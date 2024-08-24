#ifndef _FAUST_FIRESONBP_HPP_
#define _FAUST_FIRESONBP_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiResonbp;
}

namespace lr { namespace fs {

struct FiResonbpWord : public NativeWord {
    FiResonbpWord() { dsp = nullptr; }
    virtual ~FiResonbpWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiResonbpWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;
    FAUSTFLOAT* q_;
    FAUSTFLOAT* gain_;

    mydsp::FiResonbp* dsp;
    
Vec outputs_[1];

};

}}
#endif

