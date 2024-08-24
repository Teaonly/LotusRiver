#include <fstream>
#include <iostream>
#include <sstream>
#include <numeric>
#include <Eigen/Core>
#include <Eigen/StdVector>

#include "lr.hpp"
#include "nn/wavenet.hpp"

/*
def forward(self, x):
    out = x
    skips = []
    out = self.input_layer(out)

    for hidden, residual in zip(self.hidden, self.residuals):
        x = out
        out_hidden = hidden(x)

        # gated activation
        #   split (32,16,3) into two (16,16,3) for tanh and sigm calculations
        out_hidden_split = torch.split(out_hidden, self.num_channels, dim=1)
        out = torch.tanh(out_hidden_split[0]) * torch.sigmoid(out_hidden_split[1])

        skips.append(out)

        out = residual(out)
        out = out + x[:, :, -out.size(2) :]

    # modified "postprocess" step:
    out = torch.cat([s[:, :, -out.size(2) :] for s in skips], dim=1)
    out = self.linear_mix(out)
    return out
*/

namespace lr { namespace nn { namespace wavenet {


// help functions
float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

void InputLayer::process(const float* data, size_t number) {
    if ( out_.size() < number *  kernel_.size() ) {
        out_.resize(number * kernel_.size());
    }

    // change input from 1 channel to multipule channels
    for (size_t i = 0; i < number; i++) {
        float* target = out_.data() + i * kernel_.size();

        for (size_t j = 0; j < kernel_.size(); j++) {
            target[j] = kernel_[j] * data[i] + bias_[j];
        }
    }
}

void HiddenLayer::process(const std::vector<float>& data, size_t number) {
    lr_assert(data.size() == number * channels_, "Input must has same channels with define");

    // preparing memory for skip and next out
    if ( out_.size() < number * channels_ ) {
        out_.resize(number * channels_);
    }

    const float* sample = data.data();
    for ( size_t i = 0; i < number; i++) {
        processOneSample(sample, i);
        sample = sample + channels_;
    }
}

void HiddenLayer::processOneSample(const float* sample, size_t t) {
    // 0. update fifo
    for (size_t i = 0; i < channels_; i++) {
        fifo_[fifo_cursor_ * channels_ + i] = sample[i];
    }
    fifo_cursor_ ++;
    if ( fifo_cursor_ >= fifo_order_ ) {
        fifo_cursor_ = 0;
    }

    // 1. update gate conv ouput
    for (size_t i = 0; i < channels_ * 2; i++) {
        const float* w = gate_kernel_.data() + i * channels_ * kernel_size_;
        const float* b = gate_bias_.data() + i;

        float out = 0.0;
        for (size_t j = 0; j < kernel_size_; j++) {
            const float* x = fifo_get(j);
            for (size_t k = 0; k < channels_; k++) {
                out = out + x[k] * w[j + k * kernel_size_];
            }
        }
        out = out + *b;
        gate_out_[i] = out;
    }

    // 2. gated activation
    for (size_t i = 0; i < channels_; i++) {
        float o1 = tanh( gate_out_[i]);
        float o2 = sigmoid( gate_out_[i + channels_]);

        out_[t * channels_ + i ] = o1 * o2;
    }
}

const float* HiddenLayer::fifo_get(size_t kernel) {
    int pos = (int)fifo_cursor_ + kernel * dialation_;
    pos = pos % (int)fifo_order_;

    return fifo_.data() + pos * channels_;
}


void ResLayer::process(const std::vector<float>& data, const std::vector<float>& gateOut, size_t number) {
    lr_assert(data.size() == number * channels_ , "input size is wrong");
    lr_assert(gateOut.size() == number * channels_, "input size is wrong");

    if ( out_.size() < number *  channels_ ) {
        out_.resize(number * channels_);
    }

    for ( size_t t = 0; t < number; t++) {
        for (size_t i = 0; i < channels_; i++) {
            float out = 0.0;
            for (size_t j = 0; j < channels_; j++) {
                out = out + gateOut[t * channels_ + j] * kernel_[i * channels_ + j];
            }
            out = out + bias_[i];
            out_[t * channels_ + i] = out + data[t * channels_ + i];
        }
    }
}

void MixerLayer::process(const std::vector<float>& gateOut, const size_t layer, const size_t length) {
    if ( layer == 0 ) {
        if ( out_.size() != length) {
            out_.resize(length);
        }
        std::fill(out_.begin(), out_.end(), bias_[0]);
    }

    lr_assert( length == out_.size(), "output must has same size");
    for(size_t t = 0; t < length; t++) {
        float out = 0.0;
        for (size_t i = 0; i < channels_; i++) {
            out = out + gateOut[t * channels_ + i] * kernel_[layer * channels_ + i];
        }
        out_[t] = out_[t] + out;
    }
}

WaveNet::~WaveNet() {

}

void WaveNet::init() {
    current_weight_ = "filter.input_layer.";
    input_ = new InputLayer(channels_, this);

    for (size_t i = 0; i < dialations_.size(); i++) {
        std::stringstream ss;
        ss << "filter.hidden." << i << ".";
        current_weight_ = ss.str();

        auto hidden = new  HiddenLayer(channels_, dialations_[i], kernel_size_, this);
        hiddens_.push_back( hidden );
    }

    for (size_t i = 0; i < dialations_.size(); i++) {
        std::stringstream ss;
        ss << "filter.residuals." << i << ".";
        current_weight_ = ss.str();

        auto hidden = new  ResLayer(channels_, this);
        residuals_.push_back( hidden );
    }

    current_weight_ = "filter.linear_mix.";
    mixer_ = new MixerLayer(channels_, dialations_.size(), this);

    current_weight_ = "";
}

void WaveNet::new_weight(std::vector<float>& w, std::vector<float>& b) {
    lr_assert(current_weight_ != "", "target vector name error");

    std::string wname = current_weight_ + "weight";
    std::vector<float>& w_ = weights_[ wname ];
    lr_assert(w_.size() == w.size(), " weight vector must has same size");
    w.assign(w_.begin(), w_.end());

    std::string bname = current_weight_ + "bias";
    std::vector<float>& b_ = weights_[ bname ];

    lr_assert(b_.size() == b.size(), " weight vector must has same size");
    b.assign(b_.begin(), b_.end());
}

void WaveNet::load_weight(const char* file_name) {
    std::ifstream wfile(file_name);
    lr_assert(wfile.is_open(), "Can't open weight file");

    std::string line;
    std::string name;
    std::vector<float> vec;
    while (getline( wfile, line)) {
        if ( line.find("- ") == 0) {
            if ( vec.size() > 0 ) {
                weights_[name] = vec;
                vec.clear();
            }
            name = line.substr(2, line.size() - 3);
        } else if ( line.find("  - ") == 0 ) {
            std::stringstream ss(line.substr(4));
            float v;
            ss >> v;
            vec.push_back(v);
        }
    }

    if ( vec.size() > 0 ) {
        weights_[name] = vec;
    }
}

void WaveNet::process(const float* data, size_t length) {
    input_->process(data, length);

    auto out = input_->output();
    for (size_t i = 0; i < dialations_.size(); i++) {
        hiddens_[i]->process( out, length);

        mixer_->process( hiddens_[i]->output(), i, length);

        if ( i == dialations_.size() - 1 ) {
            break;
        }
        residuals_[i]->process( out, hiddens_[i]->output(), length);
        out = residuals_[i]->output();
    }
}

void ReverbWord::load_weight(const char* file_name) {
    std::ifstream wfile(file_name);
    lr_assert(wfile.is_open(), "Can't open weight file");

    std::vector<float>  allBlobs;
    std::string line;
    while (getline( wfile, line)) {
        if ( line.find("- ") == 0) {
            std::stringstream ss(line.substr(2));
            float v; ss >> v;
            allBlobs.push_back(v);
        } else {
            lr_panic("Reverb weight file format error!");
        }
    }

    const int REVERB_FIR_LENGTH = allBlobs.size();

    for (int i = 0; i < REVERB_FIR_LENGTH; i++) {
        fir_impulse.push_back(allBlobs[REVERB_FIR_LENGTH - i - 1]);
    }
    for (int i = 0; i < REVERB_FIR_LENGTH; i++) {
        fir_impulse.push_back(allBlobs[REVERB_FIR_LENGTH - i - 1]);
    }

    fir_fifo.resize(REVERB_FIR_LENGTH, 0.0);
    fifo_wp = 0;
}

void ReverbWord::run(Stack& stack) {
    const char* yaml = stack.pop_string();
    if ( fir_impulse.size() == 0) {
        load_weight(yaml);
    }

    const float* din = nullptr;
    float* dout = nullptr;
    int din_size = -1;

    float a, b;
    if ( stack.top().is_vector() ) {
        auto vin = stack.pop_vector();
        if ( out.size() != vin->size() ) {
            out = Vec::Zero(vin->size(), 1);
        }
        din = vin->data();
        din_size = vin->size();
        dout = out.data();
    } else {
        a = stack.pop_number();
        din = &a;
        din_size = 1;
        dout = &b;
    }
    const int REVERB_FIR_LENGTH = fir_fifo.size();
    for ( int i = 0; i < din_size; i++) {
        auto sample = din[i];

        fir_fifo[fifo_wp] = sample;
		fifo_wp = (fifo_wp + 1) % REVERB_FIR_LENGTH;

        auto imbegin = fir_impulse.begin() + (REVERB_FIR_LENGTH - fifo_wp);
        float new_sample = std::inner_product(fir_fifo.begin(), fir_fifo.end(), imbegin, 0.0);

        dout[i] = new_sample;
    }

    if ( din_size == 1) {
        stack.push_number( dout[0] );
        return;
    }
    stack.push_vector(&out);
}


}}}
