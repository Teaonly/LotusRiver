#ifndef _FAUST_ZZSELECT_HPP_
#define _FAUST_ZZSELECT_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzSelect;
}

namespace lr { namespace fs {

struct ZzSelectWord : public NativeWord {
    ZzSelectWord() { dsp = nullptr; }
    virtual ~ZzSelectWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzSelectWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::ZzSelect* dsp;
    
Vec outputs_[1];

};

}}
#endif

