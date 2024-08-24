#ifndef _FAUST_ZZTPORT_HPP_
#define _FAUST_ZZTPORT_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzTport;
}

namespace lr { namespace fs {

struct ZzTportWord : public NativeWord {
    ZzTportWord() { dsp = nullptr; }
    virtual ~ZzTportWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzTportWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* cx_;

    mydsp::ZzTport* dsp;
    
Vec outputs_[1];

};

}}
#endif

