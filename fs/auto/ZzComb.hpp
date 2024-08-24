#ifndef _FAUST_ZZCOMB_HPP_
#define _FAUST_ZZCOMB_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzComb;
}

namespace lr { namespace fs {

struct ZzCombWord : public NativeWord {
    ZzCombWord() { dsp = nullptr; }
    virtual ~ZzCombWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzCombWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* rtime_;
    FAUSTFLOAT* coef_y_;
    FAUSTFLOAT* coef_x_;

    mydsp::ZzComb* dsp;
    
Vec outputs_[1];

};

}}
#endif

