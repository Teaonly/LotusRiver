#ifndef _FAUST_BABITCRUSHER_HPP_
#define _FAUST_BABITCRUSHER_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class BaBitcrusher;
}

namespace lr { namespace fs {

struct BaBitcrusherWord : public NativeWord {
    BaBitcrusherWord() { dsp = nullptr; }
    virtual ~BaBitcrusherWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(BaBitcrusherWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* nbits_;

    mydsp::BaBitcrusher* dsp;
    
Vec outputs_[1];

};

}}
#endif

