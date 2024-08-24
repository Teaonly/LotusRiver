#ifndef _FAUST_BAPULSE_HPP_
#define _FAUST_BAPULSE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class BaPulse;
}

namespace lr { namespace fs {

struct BaPulseWord : public NativeWord {
    BaPulseWord() { dsp = nullptr; }
    virtual ~BaPulseWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(BaPulseWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* length_;

    mydsp::BaPulse* dsp;
    
Vec outputs_[1];

};

}}
#endif

