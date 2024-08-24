#ifndef _FAUST_FIBANDPASS6E_HPP_
#define _FAUST_FIBANDPASS6E_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiBandpass6e;
}

namespace lr { namespace fs {

struct FiBandpass6eWord : public NativeWord {
    FiBandpass6eWord() { dsp = nullptr; }
    virtual ~FiBandpass6eWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiBandpass6eWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiBandpass6e* dsp;
    
Vec outputs_[1];

};

}}
#endif

