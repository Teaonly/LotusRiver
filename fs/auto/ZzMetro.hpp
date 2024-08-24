#ifndef _FAUST_ZZMETRO_HPP_
#define _FAUST_ZZMETRO_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzMetro;
}

namespace lr { namespace fs {

struct ZzMetroWord : public NativeWord {
    ZzMetroWord() { dsp = nullptr; }
    virtual ~ZzMetroWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzMetroWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* bpm_;

    mydsp::ZzMetro* dsp;
    
Vec outputs_[1];

};

}}
#endif

