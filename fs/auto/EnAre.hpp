#ifndef _FAUST_ENARE_HPP_
#define _FAUST_ENARE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class EnAre;
}

namespace lr { namespace fs {

struct EnAreWord : public NativeWord {
    EnAreWord() { dsp = nullptr; }
    virtual ~EnAreWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(EnAreWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* attack_;
    FAUSTFLOAT* release_;

    mydsp::EnAre* dsp;
    
Vec outputs_[1];

};

}}
#endif

