#ifndef _FAUST_ZZSWITCH_HPP_
#define _FAUST_ZZSWITCH_HPP_

#include "lr.hpp"
#include "fs/dsp.hpp"

namespace mydsp {
    class ZzSwitch;
}

namespace lr { namespace fs {

struct ZzSwitchWord : public NativeWord {
    ZzSwitchWord() { dsp = nullptr; }
    virtual ~ZzSwitchWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(ZzSwitchWord)

private:
    void none_input(int bs, Stack& stack);
    void signals_input(Stack& stack);
    void vectors_input(Stack& stack);

private:

    mydsp::ZzSwitch* dsp;
    
Vec outputs_[1];

};

}}
#endif

