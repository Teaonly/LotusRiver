#include <sstream>
#include <iostream>

#include "fs/tools.hpp"
#include "zz/zz_trigseq.hpp"
#include "zz/zz_upsampler.hpp"

namespace lr { namespace zz {

struct TrigSwitch : public NativeWord {
    TrigSwitch() {
        mode_ = 0;
    }
    virtual ~TrigSwitch() {}
    virtual void run(Stack& stack) {
        auto a = stack.pop();
        auto b = stack.pop();
        auto trig = stack.pop();

        if ( trig.is_number() ) {
            float t = trig.as_number();
            if ( t ) {
                mode_ = 1 - mode_;
            }
            if ( mode_ ) {
                stack.push_number( a.as_number() );
            } else {
                stack.push_number( b.as_number() );
            }
            return;
        }

        auto vin = trig.as_vector();
        auto va = a.as_vector();
        auto vb = a.as_vector();

        if ( vin->size() != out_.size() ) {
            out_ = Vec::Zero(vin->rows(), vin->cols());
        }
        lr_assert(out_.size() == va->size(), "input signals must has same size");
        lr_assert(out_.size() == vb->size(), "input signals must has same size");

        const float* din = vin->data();
        const float* da = va->data();
        const float* db = vb->data();
        float* dout = out_.data();
        for (int i = 0; i < vin->size(); i++) {
            if (*din) {
                mode_ = 1 - mode_;
            }
            if ( mode_ ) {
                *dout = *da;
            } else {
                *dout = *db;
            }

            din++;
            dout++;
            da++;
            db++;
        }

        stack.push_vector(&out_);

    }

    NWORD_CREATOR_DEFINE_LR(TrigSwitch)
private:
    Vec out_;
    int mode_;
};



void init_words(Enviroment& env) {
    env.insert_native_word("zz.tseq", TrigSeq::creator);
    env.insert_native_word("zz.upsampler", UpSampler::creator);
}

}}
