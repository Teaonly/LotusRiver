#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <signal.h>
#include <unistd.h>

#include "lr.hpp"
#include "fs/fs_impl.hpp"
#include "zz/zz_impl.hpp"
#include "io/io_impl.hpp"
#include "io/RtMidi.h"
#include "io/RtAudio.h"
#include "nn/nn_impl.hpp"

std::string fileToString(const char* filename) {
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    return str;
}

struct MidiInHandler {
    MidiInHandler() {
        midi_ = nullptr;
    }
    virtual ~MidiInHandler() {
        if ( midi_ != nullptr) {
            delete midi_;
        }
    }

    void init(int port) {
        if ( midi_ == nullptr) {
            try {
                midi_ = new RtMidiIn();
                midi_->setCallback(&MidiInHandler::midiCallback, (void*)this);
                midi_->openPort(port);
            }
            catch (RtMidiError& error) {
                //error.printMessage();
                std::cerr << "Open MIDI failed, there is no midi device!" << std::endl;
            }
        }
    }

    int pop_message(lr::io::MidiMessage& message) {
        if (msg_queue_.size() == 0) {
            return 0;
        }
        msg_mutex_.lock();
        message = msg_queue_.front();
        msg_queue_.pop();
        msg_mutex_.unlock();
        return 1;
    }

private:
    // message handler
    static void midiCallback(double timeStamp, std::vector<unsigned char>* bytes, void* ptr);
    void push_message(lr::io::MidiMessage& message) {
        msg_mutex_.lock();
        msg_queue_.push(std::move(message));
        msg_mutex_.unlock();
    }

private:
    // MIDI control message
    RtMidiIn* midi_;

    std::mutex msg_mutex_;
    std::queue<lr::io::MidiMessage> msg_queue_;
};

void MidiInHandler::midiCallback(double timeStamp, std::vector<unsigned char>* bytes, void* ptr) {
    MidiInHandler* wd = (MidiInHandler *)ptr;
    lr::io::MidiMessage msg = lr::io::MidiMessage::parse(bytes->data(), bytes->size());
    wd->push_message(msg);
}

const size_t TICK_BUFFER_SIZE = 1024 * 1024;
const size_t ONCE_LOOP = 16;
const size_t TICK_BUFFER = 128;

struct MonoPerformer {
    MonoPerformer(lr::Enviroment& env, std::string& codes, int sr, int midi_port = 0, int bs = TICK_BUFFER) {
        buffer_.resize(TICK_BUFFER_SIZE, 0);
        cursor_ = 0;
        len_ = 0;

        perform_ = this;
        env.insert_native_word("mono.midi", MonoPerformer::creator);
        rt_ = env.new_runtime(codes);

        // dummy only once, to creating internal stuff
        rt_->run();
        rt_->stack().clear();

        // midi in init
        midi_.init(midi_port);

        // audio out init
        RtAudio::StreamParameters parameters;
        parameters.deviceId = dac_.getDefaultOutputDevice();
        parameters.nChannels = 1;
        RtAudioFormat format = RTAUDIO_FLOAT32;
        unsigned int bufferFrames = bs;

        try {
            dac_.openStream( &parameters, NULL, format, sr, &bufferFrames, &MonoPerformer::tick, (void *)this );
            dac_.startStream();
        } catch ( RtAudioErrorType& error ) {
            lr_panic("Open and start realtime audio output error!");
        }
    }
    virtual ~MonoPerformer() {
        if ( perform_ == nullptr) {
            return;
        }
        try {
            dac_.closeStream();
        }
        catch ( RtAudioErrorType &error ) {
            lr_panic("Close reatime audio error!");
        }

        perform_ = nullptr;
        delete rt_;
    }

    void run_once() {
        rt_->run();

        // Copy output from vector
        if ( rt_->stack().top().is_vector() ) {
            auto vec = rt_->stack().pop_vector();
            const float* src = vec->data();
            for (int i = 0; i < vec->size(); i++) {
                buffer_[i] = src[i];
            }
            cursor_ = 0;
            len_ = vec->size();

            lr_assert( rt_->stack().size() == 0, " Stack must be empty");
            return;
        }

        buffer_[0] = rt_->stack().pop_number();
        for (size_t i = 1; i < ONCE_LOOP; i++) {
            rt_->run();

            buffer_[i] = rt_->stack().pop_number();
            lr_assert( rt_->stack().size() == 0, " Stack must be empty");
        }

        cursor_ = 0;
        len_ = ONCE_LOOP;
    }

private:
    static int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                     double streamTime, RtAudioStreamStatus status, void *userData );

    lr::Runtime* rt_;
    MidiInHandler midi_;
    RtAudio dac_;

    std::vector<float> buffer_;
    size_t cursor_;
    size_t len_;

    static MonoPerformer* perform_;
    static lr::NativeWord* creator(lr::Enviroment& env) {
        struct MonoMidi: public lr::NativeWord {
            MonoMidi() {
                lr_assert(perform_ != nullptr, "Internal pointer can't be empty!");
            }
            virtual ~MonoMidi() {
            }
            virtual void run(lr::Stack& stack) {
                auto msg = lr::io::MidiMessage::null();
                perform_->midi_.pop_message(msg);
                stack.push_number(msg.value_);
            }
        };

        return new MonoMidi();
    }
};

MonoPerformer* MonoPerformer::perform_ = nullptr;

int MonoPerformer::tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                        double streamTime, RtAudioStreamStatus status, void *userData ) {
    MonoPerformer* thiz = (MonoPerformer *)userData;
    float * outSamples = (float *)outputBuffer;

    size_t outlen = nBufferFrames;

    while( outlen > 0 ) {
        if ( thiz->len_ == 0 ) {
            thiz->run_once();
        }

        size_t used = std::min(outlen, thiz->len_);
        for(size_t i = 0; i < used; i++) {
            outSamples[i] = thiz->buffer_[thiz->cursor_ + i];
        }

        outSamples += used;
        outlen -= used;

        thiz->cursor_ += used;
        thiz->len_ -= used;
    }

    return 0;
}

static bool stop_flag = false;
static void finish(int ignore) {
    stop_flag = true;
}

int main(int argc, const char* argv[] ) {
    if ( argc < 3 ) {
        std::cout << "synth <sample_rate>  <code_file0> ..." << std::endl;
        return 0;
    }
    const int sr = atoi( argv[1] );
    if ( sr < 8000) {
        std::cout << "Sample rate can't be lower than 8K " << std::endl;
        return 0;
    }

    lr::Enviroment env(sr);
    lr::zz::init_words(env);
    lr::io::init_words(env);
    lr::fs::init_words(env);
    lr::nn::init_words(env);

    std::string codes;
    for (int i = 2; i < argc; i++) {
        auto txt = fileToString(argv[i]);
        codes = codes + "\n" + txt;
    }

    signal(SIGINT, finish);

    MonoPerformer performer(env, codes, sr);

    while(stop_flag == false) {
        usleep(10 * 1000);
    }
}
