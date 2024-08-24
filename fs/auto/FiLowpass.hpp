#ifndef _FAUST_FILOWPASS_HPP_
#define _FAUST_FILOWPASS_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiLowpass;
}

namespace lr { namespace fs {

struct FiLowpassWord : public NativeWord {
    FiLowpassWord() { dsp = nullptr; }
    virtual ~FiLowpassWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiLowpassWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiLowpass* dsp;
    
Vec outputs_[1];

};

}}
#endif

