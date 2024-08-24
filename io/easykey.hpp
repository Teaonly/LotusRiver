#ifndef _IO_EASYKEY_HPP_
#define _IO_EASYKEY_HPP_

#include "io/io_impl.hpp"
#include "fs/tools.hpp"
#include "fs/dsp.hpp"
#include "fs/auto/EnAre~.hpp"
#include "fs/auto/ZzVibrato~.hpp"

namespace lr { namespace io {

struct EasyMonoKeyboard : public NativeWord {
    EasyMonoKeyboard() {
        last_key_ = 0;

        pitch_ = 0;
        pitch_from_ = 0;
        pitch_to_ = 0;
        loud_ = 0;
        loud_from_ = 0;
        loud_to_ = 0;

        const int sr = 1000;
        are_p.init(sr);
        are_l.init(sr);
        vib_p.init(sr);
        vib_l.init(sr);

        {
            mydsp::EasyUI ui;
            are_p.buildUserInterface(&ui);
            *ui.value("attack") = 0.02;
            *ui.value("release") = 0.01;
        }

        {
            mydsp::EasyUI ui;
            are_l.buildUserInterface(&ui);
            *ui.value("attack") = 0.1;
            *ui.value("release") = 0.3;
        }

        {
            mydsp::EasyUI ui;
            vib_p.buildUserInterface(&ui);
            *ui.value("freq") = 3.5;
            *ui.value("phase") = 0.0;
            *ui.value("attack") = 2.0;
            *ui.value("release") = 0.0;
        }

        {
            mydsp::EasyUI ui;
            vib_l.buildUserInterface(&ui);
            *ui.value("freq") = 3.5;
            *ui.value("phase") = 1.57;
            *ui.value("attack") = 1.5;
            *ui.value("release") = 0.0;
        }
    }

    virtual ~EasyMonoKeyboard() { }

    virtual void run(Stack& stack) {
        MidiMessage msg;
        msg.value_ = stack.pop_number();

        FAUSTFLOAT out = 0.0;
        FAUSTFLOAT* pout = &out;
        FAUSTFLOAT trig = 0.0;
        FAUSTFLOAT* ptrig = &trig;

        if ( msg.type_  == MidiMessage::NoteOn ) {
            last_key_ = msg.dd.d1_;

            pitch_from_ = pitch_;
            pitch_to_ = lr::fs::ba_midikey2hz( last_key_ );

            loud_from_ = loud_;
            loud_to_ = (float)msg.dd.d2_ / 127.0f;

            trig = 0.0;
            vib_p.compute(1, &ptrig, &pout);
            vib_l.compute(1, &ptrig, &pout);

        } else if ( msg.type_  == MidiMessage::NoteOff ) {
            if ( msg.dd.d1_ == last_key_ ) {
                loud_from_ = loud_;
                loud_to_ = 0.0;
            }
        }

        // update pitch
        if ( pitch_to_ > pitch_from_ ) {
            trig = 1.0;
        }
        are_p.compute(1, &ptrig, &pout);
        pitch_ = update_from_to( pitch_from_, pitch_to_, out);

        // update loudness
        trig = 0.0;
        if ( loud_to_ > loud_from_ ) {
            trig = 1.0;
        }
        are_l.compute(1, &ptrig, &pout);
        loud_ = update_from_to(loud_from_, loud_to_, out);

        // apply vibrator
        trig = 0.0;
        if ( loud_to_ > 0.0 ) {
            trig = 1.0;
        }
        vib_p.compute(1, &ptrig, &pout);
        float out1 = out;
        vib_l.compute(1, &ptrig, &pout);

        float p = pitch_ + pitch_* 0.008 * out1;
        float l = loud_ + 0.1 * loud_ * out;

        float rnd = (float)(random() % 1000 - 500) / 1000.0;
        p = p + pitch_ * 0.001 * rnd;
        rnd = (float)(random() % 1000 - 500) / 1000.0;
        l = l + rnd * 0.01;

        stack.push_number(p);
        stack.push_number(l);
    }

    float update_from_to(float from, float to, float q) {
        float ret = std::max(from, to) * q + (1.0 - q) * std::min(from, to);
        return ret;
    }

    NWORD_CREATOR_DEFINE_LR(EasyMonoKeyboard)
private:

    float pitch_;
    float pitch_from_;
    float pitch_to_;
    float loud_;
    float loud_from_;
    float loud_to_;

    mydsp::EnAre are_p;
    mydsp::EnAre are_l;

    mydsp::ZzVibrato vib_p;
    mydsp::ZzVibrato vib_l;

    // mono mode only
    unsigned char last_key_;
};

}}
#endif
