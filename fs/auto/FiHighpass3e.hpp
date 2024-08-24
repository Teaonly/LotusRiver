#ifndef _FAUST_FIHIGHPASS3E_HPP_
#define _FAUST_FIHIGHPASS3E_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiHighpass3e;
}

namespace lr { namespace fs {

struct FiHighpass3eWord : public NativeWord {
    FiHighpass3eWord() { dsp = nullptr; }
    virtual ~FiHighpass3eWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiHighpass3eWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fc_;

    mydsp::FiHighpass3e* dsp;
    
Vec outputs_[1];

};

}}
#endif

