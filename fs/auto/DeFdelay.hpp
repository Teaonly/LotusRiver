#ifndef _FAUST_DEFDELAY_HPP_
#define _FAUST_DEFDELAY_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class DeFdelay;
}

namespace lr { namespace fs {

struct DeFdelayWord : public NativeWord {
    DeFdelayWord() { dsp = nullptr; }
    virtual ~DeFdelayWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(DeFdelayWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* d_;

    mydsp::DeFdelay* dsp;
    
Vec outputs_[1];

};

}}
#endif

