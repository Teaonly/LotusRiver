#ifndef _FAUST_ENADSR_HPP_
#define _FAUST_ENADSR_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class EnAdsr;
}

namespace lr { namespace fs {

struct EnAdsrWord : public NativeWord {
    EnAdsrWord() { dsp = nullptr; }
    virtual ~EnAdsrWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(EnAdsrWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* attack_;
    FAUSTFLOAT* decay_;
    FAUSTFLOAT* sustain_;
    FAUSTFLOAT* release_;

    mydsp::EnAdsr* dsp;
    
Vec outputs_[1];

};

}}
#endif

