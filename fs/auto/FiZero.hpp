#ifndef _FAUST_FIZERO_HPP_
#define _FAUST_FIZERO_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiZero;
}

namespace lr { namespace fs {

struct FiZeroWord : public NativeWord {
    FiZeroWord() { dsp = nullptr; }
    virtual ~FiZeroWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiZeroWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* z_;

    mydsp::FiZero* dsp;
    
Vec outputs_[1];

};

}}
#endif

