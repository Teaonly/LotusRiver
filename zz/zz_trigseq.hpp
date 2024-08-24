#ifndef _ZZ_TRIGSEQ_HPP_
#define _ZZ_TRIGSEQ_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace lr { namespace zz {

struct TrigSeq : public NativeWord {
    TrigSeq() {}
    virtual ~TrigSeq() {}

    virtual void run(Stack& stack) {
        const char* seq = stack.pop_string();
        if ( tab_.size() == 0) {
            std::stringstream ss;
            ss << seq;
            float num;
            while ( ss >> num ) {
                tab_.push_back( num );
            }
            lr_assert( tab_.size() > 0, "TrigSeq can't read number from buffer!");

            pos_ = -1;
        }

        const int shuf = stack.pop_number();
        if ( stack.top().is_number() ) {
            do_scalar(stack, shuf);
        } else {
            do_vector(stack, shuf);
        }
    }
    void do_scalar(Stack& stack,const int shuf) {
        float trig = stack.pop_number();
        if ( trig != 0.0 ) {
            if ( shuf ) {
                float r = fs::random();
                pos_ = (int)(1.0 * r * tab_.size()) % tab_.size();
            } else {
                pos_ = (pos_ + 1) % tab_.size();
            }
        }
        stack.push_number( tab_[pos_] );
    }

    void do_vector(Stack& stack, const int shuf ) {
        auto vin = stack.pop_vector();
        if ( out_.size() != vin->size() ) {
            out_ = Vec::Zero(vin->rows(), vin->cols());
        }

        float* dout = out_.data();
        const float* din = vin->data();
        for(int i = 0; i < vin->size(); i++) {
            if ( din[i] != 0.0 ) {
                if ( shuf ) {
                    float r = fs::random();
                    pos_ = (int)(1.0 * r * tab_.size()) % tab_.size();
                } else {
                    pos_ = (pos_ + 1) % tab_.size();
                }

                dout[i] = tab_[pos_];
            }
        }

        stack.push_vector( &out_ );
    }

    NWORD_CREATOR_DEFINE_LR(TrigSeq)
private:
    Vec out_;
    std::vector<float> tab_;
    int pos_;
};

}}
#endif
