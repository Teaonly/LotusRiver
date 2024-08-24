#ifndef _FAUST_BABEAT_HPP_
#define _FAUST_BABEAT_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class BaBeat;
}

namespace lr { namespace fs {

struct BaBeatWord : public NativeWord {
    BaBeatWord() { dsp = nullptr; }
    virtual ~BaBeatWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(BaBeatWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* bpm_;

    mydsp::BaBeat* dsp;
    
Vec outputs_[1];

};

}}
#endif

