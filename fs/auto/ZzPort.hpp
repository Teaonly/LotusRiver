#ifndef _FAUST_ZZPORT_HPP_
#define _FAUST_ZZPORT_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzPort;
}

namespace lr { namespace fs {

struct ZzPortWord : public NativeWord {
    ZzPortWord() { dsp = nullptr; }
    virtual ~ZzPortWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzPortWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* cx_;

    mydsp::ZzPort* dsp;
    
Vec outputs_[1];

};

}}
#endif

