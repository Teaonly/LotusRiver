#ifndef _FAUST_DEDELAY_HPP_
#define _FAUST_DEDELAY_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class DeDelay;
}

namespace lr { namespace fs {

struct DeDelayWord : public NativeWord {
    DeDelayWord() { dsp = nullptr; }
    virtual ~DeDelayWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(DeDelayWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* d_;

    mydsp::DeDelay* dsp;
    
Vec outputs_[1];

};

}}
#endif

