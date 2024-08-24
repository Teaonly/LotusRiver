#ifndef _FAUST_FILOWPASS6E_HPP_
#define _FAUST_FILOWPASS6E_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiLowpass6e;
}

namespace lr { namespace fs {

struct FiLowpass6eWord : public NativeWord {
    FiLowpass6eWord() { dsp = nullptr; }
    virtual ~FiLowpass6eWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiLowpass6eWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiLowpass6e* dsp;
    
Vec outputs_[1];

};

}}
#endif

