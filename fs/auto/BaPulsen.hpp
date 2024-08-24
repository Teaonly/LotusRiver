#ifndef _FAUST_BAPULSEN_HPP_
#define _FAUST_BAPULSEN_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class BaPulsen;
}

namespace lr { namespace fs {

struct BaPulsenWord : public NativeWord {
    BaPulsenWord() { dsp = nullptr; }
    virtual ~BaPulsenWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(BaPulsenWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* length_;
    FAUSTFLOAT* period_;

    mydsp::BaPulsen* dsp;
    
Vec outputs_[1];

};

}}
#endif

