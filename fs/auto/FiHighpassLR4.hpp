#ifndef _FAUST_FIHIGHPASSLR4_HPP_
#define _FAUST_FIHIGHPASSLR4_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiHighpassLR4;
}

namespace lr { namespace fs {

struct FiHighpassLR4Word : public NativeWord {
    FiHighpassLR4Word() { dsp = nullptr; }
    virtual ~FiHighpassLR4Word();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiHighpassLR4Word)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* cf_;

    mydsp::FiHighpassLR4* dsp;
    
Vec outputs_[1];

};

}}
#endif

