#ifndef _FAUST_OSOSCF_HPP_
#define _FAUST_OSOSCF_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class OsOscF;
}

namespace lr { namespace fs {

struct OsOscFWord : public NativeWord {
    OsOscFWord() { dsp = nullptr; }
    virtual ~OsOscFWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(OsOscFWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::OsOscF* dsp;
    
Vec outputs_[1];

};

}}
#endif

