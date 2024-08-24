#ifndef _FAUST_ZZTICK_HPP_
#define _FAUST_ZZTICK_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzTick;
}

namespace lr { namespace fs {

struct ZzTickWord : public NativeWord {
    ZzTickWord() { dsp = nullptr; }
    virtual ~ZzTickWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzTickWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::ZzTick* dsp;
    
Vec outputs_[1];

};

}}
#endif

