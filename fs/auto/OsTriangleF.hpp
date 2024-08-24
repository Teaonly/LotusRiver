#ifndef _FAUST_OSTRIANGLEF_HPP_
#define _FAUST_OSTRIANGLEF_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsTriangleF;
}

namespace lr { namespace fs {

struct OsTriangleFWord : public NativeWord {
    OsTriangleFWord() { dsp = nullptr; }
    virtual ~OsTriangleFWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsTriangleFWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::OsTriangleF* dsp;
    
Vec outputs_[1];

};

}}
#endif

