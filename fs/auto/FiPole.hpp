#ifndef _FAUST_FIPOLE_HPP_
#define _FAUST_FIPOLE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiPole;
}

namespace lr { namespace fs {

struct FiPoleWord : public NativeWord {
    FiPoleWord() { dsp = nullptr; }
    virtual ~FiPoleWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiPoleWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* p_;

    mydsp::FiPole* dsp;
    
Vec outputs_[1];

};

}}
#endif

