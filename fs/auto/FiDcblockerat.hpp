#ifndef _FAUST_FIDCBLOCKERAT_HPP_
#define _FAUST_FIDCBLOCKERAT_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class FiDcblockerat;
}

namespace lr { namespace fs {

struct FiDcblockeratWord : public NativeWord {
    FiDcblockeratWord() { dsp = nullptr; }
    virtual ~FiDcblockeratWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FiDcblockeratWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:
    FAUSTFLOAT* fb_;

    mydsp::FiDcblockerat* dsp;
    
Vec outputs_[1];

};

}}
#endif

