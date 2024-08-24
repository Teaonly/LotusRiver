#ifndef _FAUST_FIRESONHP_HPP_
#define _FAUST_FIRESONHP_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiResonhp;
}

namespace lr { namespace fs {

struct FiResonhpWord : public NativeWord {
    FiResonhpWord() { dsp = nullptr; }
    virtual ~FiResonhpWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiResonhpWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;
    FAUSTFLOAT* q_;
    FAUSTFLOAT* gain_;

    mydsp::FiResonhp* dsp;
    
Vec outputs_[1];

};

}}
#endif

