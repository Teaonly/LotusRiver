#ifndef _FAUST_ZZFM_HPP_
#define _FAUST_ZZFM_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzFm;
}

namespace lr { namespace fs {

struct ZzFmWord : public NativeWord {
    ZzFmWord() { dsp = nullptr; }
    virtual ~ZzFmWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzFmWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* carry_;
    FAUSTFLOAT* modulator_;
    FAUSTFLOAT* index_;

    mydsp::ZzFm* dsp;
    
Vec outputs_[1];

};

}}
#endif

