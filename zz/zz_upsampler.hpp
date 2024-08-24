#ifndef _ZZ_UPSAMPLER_HPP_
#define _ZZ_UPSAMPLER_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace lr { namespace zz {

struct UpSampler : public NativeWord {
    UpSampler() {
        last_ = 0.0;
    }
    virtual ~UpSampler(){};
    virtual void run(Stack& stack) {
        int up_ = stack.pop_number();

        if (up_ == 1) {
            if ( stack.top().is_number() ) {
                auto d = stack.pop_number();
                stack.push_number(d);
                return;
            }
            auto d = stack.pop_vector();
            stack.push_vector(d);
            return;
        }


        if ( stack.top().is_number() ) {
            if ( out_.size() != up_ ) {
                out_ = Vec::Zero(up_, 1);
            }

            float v = stack.pop_number();
            float* dout = out_.data();
            for(int i = 0; i < up_; i++) {
                float split = (i + 1) / up_;

                dout[i] = (1.0 - split) * last_ + split * v;
            }
            last_ = v;

            stack.push_vector(&out_);
            return;
        }

        auto vin_ = stack.pop_vector();
        if ( out_.size() != up_ * vin_->size() ) {
            out_ = Vec::Zero( vin_->rows() * up_, vin_->cols() );
        }
        const float* din = vin_->data();
        float* dout = out_.data();

        for (int n = 0; n < vin_->size(); n++) {

            float v = *din;
            din ++;
            for(int i = 0; i < up_; i++) {
                float split = (i + 1.0) / up_;
                *dout = (1.0 - split) * last_ + split * v;
                dout++;
            }
            last_ = v;
        }
        stack.push_vector(&out_);
    }

    NWORD_CREATOR_DEFINE_LR(UpSampler)
private:
    float last_;
    Vec out_;
};

}}
#endif
