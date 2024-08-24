#ifndef _FAUST_OSSQUARE_HPP_
#define _FAUST_OSSQUARE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsSquare;
}

namespace lr { namespace fs {

struct OsSquareWord : public NativeWord {
    OsSquareWord() { dsp = nullptr; }
    virtual ~OsSquareWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsSquareWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* freq_;

    mydsp::OsSquare* dsp;
    
Vec outputs_[1];

};

}}
#endif

