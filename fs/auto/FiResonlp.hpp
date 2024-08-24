#ifndef _FAUST_FIRESONLP_HPP_
#define _FAUST_FIRESONLP_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiResonlp;
}

namespace lr { namespace fs {

struct FiResonlpWord : public NativeWord {
    FiResonlpWord() { dsp = nullptr; }
    virtual ~FiResonlpWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiResonlpWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;
    FAUSTFLOAT* q_;
    FAUSTFLOAT* gain_;

    mydsp::FiResonlp* dsp;
    
Vec outputs_[1];

};

}}
#endif

