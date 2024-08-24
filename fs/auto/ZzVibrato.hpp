#ifndef _FAUST_ZZVIBRATO_HPP_
#define _FAUST_ZZVIBRATO_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzVibrato;
}

namespace lr { namespace fs {

struct ZzVibratoWord : public NativeWord {
    ZzVibratoWord() { dsp = nullptr; }
    virtual ~ZzVibratoWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzVibratoWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* freq_;
    FAUSTFLOAT* phase_;
    FAUSTFLOAT* attack_;
    FAUSTFLOAT* release_;

    mydsp::ZzVibrato* dsp;
    
Vec outputs_[1];

};

}}
#endif

