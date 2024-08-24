#ifndef _FAUST_OSTRIANGLE_HPP_
#define _FAUST_OSTRIANGLE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsTriangle;
}

namespace lr { namespace fs {

struct OsTriangleWord : public NativeWord {
    OsTriangleWord() { dsp = nullptr; }
    virtual ~OsTriangleWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsTriangleWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* freq_;

    mydsp::OsTriangle* dsp;
    
Vec outputs_[1];

};

}}
#endif

