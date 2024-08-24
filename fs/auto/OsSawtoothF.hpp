#ifndef _FAUST_OSSAWTOOTHF_HPP_
#define _FAUST_OSSAWTOOTHF_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsSawtoothF;
}

namespace lr { namespace fs {

struct OsSawtoothFWord : public NativeWord {
    OsSawtoothFWord() { dsp = nullptr; }
    virtual ~OsSawtoothFWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsSawtoothFWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::OsSawtoothF* dsp;
    
Vec outputs_[1];

};

}}
#endif

