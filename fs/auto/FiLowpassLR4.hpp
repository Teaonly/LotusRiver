#ifndef _FAUST_FILOWPASSLR4_HPP_
#define _FAUST_FILOWPASSLR4_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiLowpassLR4;
}

namespace lr { namespace fs {

struct FiLowpassLR4Word : public NativeWord {
    FiLowpassLR4Word() { dsp = nullptr; }
    virtual ~FiLowpassLR4Word();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiLowpassLR4Word)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* cf_;

    mydsp::FiLowpassLR4* dsp;
    
Vec outputs_[1];

};

}}
#endif

