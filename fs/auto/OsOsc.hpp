#ifndef _FAUST_OSOSC_HPP_
#define _FAUST_OSOSC_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsOsc;
}

namespace lr { namespace fs {

struct OsOscWord : public NativeWord {
    OsOscWord() { dsp = nullptr; }
    virtual ~OsOscWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsOscWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* freq_;

    mydsp::OsOsc* dsp;
    
Vec outputs_[1];

};

}}
#endif

