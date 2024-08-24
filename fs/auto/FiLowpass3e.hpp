#ifndef _FAUST_FILOWPASS3E_HPP_
#define _FAUST_FILOWPASS3E_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiLowpass3e;
}

namespace lr { namespace fs {

struct FiLowpass3eWord : public NativeWord {
    FiLowpass3eWord() { dsp = nullptr; }
    virtual ~FiLowpass3eWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiLowpass3eWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiLowpass3e* dsp;
    
Vec outputs_[1];

};

}}
#endif

