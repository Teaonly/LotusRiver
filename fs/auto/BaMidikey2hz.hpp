#ifndef _FAUST_BAMIDIKEY2HZ_HPP_
#define _FAUST_BAMIDIKEY2HZ_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class BaMidikey2hz;
}

namespace lr { namespace fs {

struct BaMidikey2hzWord : public NativeWord {
    BaMidikey2hzWord() { dsp = nullptr; }
    virtual ~BaMidikey2hzWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(BaMidikey2hzWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::BaMidikey2hz* dsp;
    
Vec outputs_[1];

};

}}
#endif

