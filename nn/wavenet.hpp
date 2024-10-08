#ifndef _NN_CONV_HPP_
#define _NN_CONV_HPP_

#include <map>
#include <vector>
#include "lr.hpp"

namespace lr { namespace nn { namespace wavenet {

struct ParameterRegister {
    virtual void new_weight(std::vector<float>& w, std::vector<float>& b) = 0;
};

struct InputLayer {
    InputLayer(const size_t out_channels, ParameterRegister* reg) {
        kernel_.resize(out_channels);
        bias_.resize(out_channels);

        reg->new_weight(kernel_, bias_);
    }

    void process(const float* data, size_t number);

    const std::vector<float>& output() {
        return out_;
    }

private:
    std::vector<float> kernel_;
    std::vector<float> bias_;
    std::vector<float> out_;
};

struct HiddenLayer {
    HiddenLayer(const size_t channels,
                const size_t dialation,
                const size_t kernel_size,
                ParameterRegister* reg) :
        channels_(channels), dialation_(dialation), kernel_size_(kernel_size) ,
        fifo_order_( (kernel_size - 1) * dialation + 1) {

        gate_kernel_.resize(2 * channels * channels * kernel_size);
        gate_bias_.resize(2 * channels);
        gate_out_.resize(2 * channels);

        fifo_.resize(fifo_order_ * channels, 0.0);
        fifo_cursor_ = 0;

        reg->new_weight(gate_kernel_, gate_bias_);
    }

    void process(const std::vector<float>& data, size_t number);
    const std::vector<float>& output() {
        return out_;
    }

private:
    void processOneSample(const float* sample, size_t t);
    const float* fifo_get(size_t kernel);

private:
    const size_t channels_;
    const size_t dialation_;
    const size_t kernel_size_;
    const size_t fifo_order_;           // (kernel_size - 1) * dialation + 1

    std::vector<float> gate_kernel_;      // output channel * input channel * kernel size
    std::vector<float> gate_bias_;        // output channel
    std::vector<float> gate_out_;         // output channel

    std::vector<float> res_kernel_;       // channel * channel * 1
    std::vector<float> res_bias_;         // channel

    // input
    std::vector<float> fifo_;             // fifo_order * channel
    size_t fifo_cursor_;

    // output
    std::vector<float> out_;
};

struct ResLayer {
    ResLayer(const size_t channels, ParameterRegister* reg) : channels_(channels) {
        kernel_.resize(channels * channels);
        bias_.resize(channels);

        reg->new_weight(kernel_, bias_);
    }

    void process(const std::vector<float>& data, const std::vector<float>& gateOut, size_t number);
    const std::vector<float>& output() {
        return out_;
    }

private:
    const size_t channels_;
    std::vector<float> kernel_;
    std::vector<float> bias_;
    std::vector<float> out_;
};

struct MixerLayer {
    MixerLayer(const size_t channels, const size_t layers, ParameterRegister* reg) : channels_(channels) {
        kernel_.resize(channels * layers);
        bias_.resize(1);

        reg->new_weight(kernel_, bias_);
    }

    void process(const std::vector<float>& gateOut, const size_t layer, const size_t length);

    const std::vector<float>& output() {
        return out_;
    }

private:
    const size_t channels_;

    std::vector<float> kernel_;
    std::vector<float> bias_;

    std::vector<float> out_;
};


struct WaveNet : public ParameterRegister {
    WaveNet (size_t channels, size_t kernel_size, const std::vector<size_t>& dialations, const char* weight_file):
        channels_(channels), kernel_size_(kernel_size), dialations_(dialations) {

        load_weight(weight_file);
        init();
    }
    virtual ~WaveNet();
    virtual void new_weight(std::vector<float>& w, std::vector<float>& b);

    void process(const float* data, size_t length);
    const std::vector<float>& output() {
        return mixer_->output();
    }

private:
    void load_weight(const char* file_name);
    void init();

private:
    size_t  channels_;
    size_t  kernel_size_;
    std::vector<size_t> dialations_;

    std::string current_weight_;
    std::map<const std::string, std::vector<float>> weights_;

    InputLayer* input_;
    std::vector<HiddenLayer*> hiddens_;
    std::vector<ResLayer*> residuals_;
    MixerLayer* mixer_;

};



struct WaveNetWord : public lr::NativeWord {
    WaveNetWord() {
        net_ = nullptr;
    }
    virtual ~WaveNetWord() {
        if ( net_ != nullptr ) {
            delete net_;
        }
    }

    virtual void run(Stack& stack) {
        const char* file_name = stack.pop_string();
        size_t repeat = stack.pop_number();
        size_t dialation = stack.pop_number();
        size_t kernel_size = stack.pop_number();
        size_t channels = stack.pop_number();

        if ( net_ == nullptr) {
            std::vector<size_t> ds;
            for(size_t r = 0; r < repeat; r++) {
                for(size_t i = 0; i < dialation; i++) {
                    ds.push_back( 1 << i );
                }
            }
            net_ = new WaveNet(channels, kernel_size, ds, file_name);
        }

        auto v = stack.pop_vector();
        net_->process(v->data(), v->size());

        // copy to output
        auto out = net_->output();
        if ( vec.size() != (int)out.size() ) {
            vec = Vec::Zero(out.size(), 1);
        }
        auto d = vec.data();
        for (size_t i = 0; i < out.size(); i++) {
            d[i] = out[i];
        }

        stack.push_vector(&vec);
    }

    NWORD_CREATOR_DEFINE_LR(WaveNetWord)
private:
    WaveNet* net_;
    Vec vec;
};

struct ReverbWord : public lr::NativeWord {
    ReverbWord() {
    }
    virtual ~ReverbWord() {
    }

    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ReverbWord)
private:
    void load_weight(const char* file_name);

private:
    std::vector<float> fir_impulse;
    std::vector<float> fir_fifo;
    int fifo_wp;

    Vec out;
};


}}}


#endif
