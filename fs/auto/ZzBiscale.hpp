#ifndef _FAUST_ZZBISCALE_HPP_
#define _FAUST_ZZBISCALE_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzBiscale;
}

namespace lr { namespace fs {

struct ZzBiscaleWord : public NativeWord {
    ZzBiscaleWord() { dsp = nullptr; }
    virtual ~ZzBiscaleWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzBiscaleWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* low_;
    FAUSTFLOAT* up_;

    mydsp::ZzBiscale* dsp;
    
Vec outputs_[1];

};

}}
#endif

