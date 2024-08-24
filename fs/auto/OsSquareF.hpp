#ifndef _FAUST_OSSQUAREF_HPP_
#define _FAUST_OSSQUAREF_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsSquareF;
}

namespace lr { namespace fs {

struct OsSquareFWord : public NativeWord {
    OsSquareFWord() { dsp = nullptr; }
    virtual ~OsSquareFWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsSquareFWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::OsSquareF* dsp;
    
Vec outputs_[1];

};

}}
#endif

