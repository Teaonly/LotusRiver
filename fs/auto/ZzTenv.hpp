#ifndef _FAUST_ZZTENV_HPP_
#define _FAUST_ZZTENV_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzTenv;
}

namespace lr { namespace fs {

struct ZzTenvWord : public NativeWord {
    ZzTenvWord() { dsp = nullptr; }
    virtual ~ZzTenvWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzTenvWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* atk_;
    FAUSTFLOAT* hold_;
    FAUSTFLOAT* rel_;

    mydsp::ZzTenv* dsp;
    
Vec outputs_[1];

};

}}
#endif

