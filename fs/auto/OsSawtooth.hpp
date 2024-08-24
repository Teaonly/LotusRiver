#ifndef _FAUST_OSSAWTOOTH_HPP_
#define _FAUST_OSSAWTOOTH_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsSawtooth;
}

namespace lr { namespace fs {

struct OsSawtoothWord : public NativeWord {
    OsSawtoothWord() { dsp = nullptr; }
    virtual ~OsSawtoothWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsSawtoothWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* freq_;

    mydsp::OsSawtooth* dsp;
    
Vec outputs_[1];

};

}}
#endif

