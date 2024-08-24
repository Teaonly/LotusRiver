#ifndef _FAUST_REMONOFREEVERB_HPP_
#define _FAUST_REMONOFREEVERB_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ReMonoFreeverb;
}

namespace lr { namespace fs {

struct ReMonoFreeverbWord : public NativeWord {
    ReMonoFreeverbWord() { dsp = nullptr; }
    virtual ~ReMonoFreeverbWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ReMonoFreeverbWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fb1_;
    FAUSTFLOAT* fb2_;
    FAUSTFLOAT* damp_;
    FAUSTFLOAT* spread_;

    mydsp::ReMonoFreeverb* dsp;
    
Vec outputs_[1];

};

}}
#endif

