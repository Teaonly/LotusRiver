#ifndef _FAUST_ZZTENVX_HPP_
#define _FAUST_ZZTENVX_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzTenvx;
}

namespace lr { namespace fs {

struct ZzTenvxWord : public NativeWord {
    ZzTenvxWord() { dsp = nullptr; }
    virtual ~ZzTenvxWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzTenvxWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* atk_;
    FAUSTFLOAT* hold_;
    FAUSTFLOAT* rel_;

    mydsp::ZzTenvx* dsp;
    
Vec outputs_[1];

};

}}
#endif

