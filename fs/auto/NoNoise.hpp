#ifndef _FAUST_NONOISE_HPP_
#define _FAUST_NONOISE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class NoNoise;
}

namespace lr { namespace fs {

struct NoNoiseWord : public NativeWord {
    NoNoiseWord() { dsp = nullptr; }
    virtual ~NoNoiseWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(NoNoiseWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::NoNoise* dsp;
    
Vec outputs_[1];

};

}}
#endif

