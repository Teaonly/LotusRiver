#ifndef _FAUST_FIBANDPASS_HPP_
#define _FAUST_FIBANDPASS_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiBandpass;
}

namespace lr { namespace fs {

struct FiBandpassWord : public NativeWord {
    FiBandpassWord() { dsp = nullptr; }
    virtual ~FiBandpassWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiBandpassWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fl_;
    FAUSTFLOAT* fu_;

    mydsp::FiBandpass* dsp;
    
Vec outputs_[1];

};

}}
#endif

