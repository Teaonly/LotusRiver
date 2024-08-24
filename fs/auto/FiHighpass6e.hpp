#ifndef _FAUST_FIHIGHPASS6E_HPP_
#define _FAUST_FIHIGHPASS6E_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiHighpass6e;
}

namespace lr { namespace fs {

struct FiHighpass6eWord : public NativeWord {
    FiHighpass6eWord() { dsp = nullptr; }
    virtual ~FiHighpass6eWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiHighpass6eWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiHighpass6e* dsp;
    
Vec outputs_[1];

};

}}
#endif

