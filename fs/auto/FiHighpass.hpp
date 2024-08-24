#ifndef _FAUST_FIHIGHPASS_HPP_
#define _FAUST_FIHIGHPASS_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiHighpass;
}

namespace lr { namespace fs {

struct FiHighpassWord : public NativeWord {
    FiHighpassWord() { dsp = nullptr; }
    virtual ~FiHighpassWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiHighpassWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiHighpass* dsp;
    
Vec outputs_[1];

};

}}
#endif

