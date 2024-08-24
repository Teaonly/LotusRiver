#ifndef _FAUST_FACTORY_HPP_
#define _FAUST_FACTORY_HPP_

#include "lr.hpp"

class llvm_dsp_factory;
class dsp;

namespace lr { namespace fs {

struct FaustFactoryWord : public NativeWord {
    FaustFactoryWord() {
        factory_ = nullptr;
        dsp_ = nullptr;
    }
    virtual ~FaustFactoryWord();
    virtual void run(Stack& stack);

    NWORD_CREATOR_DEFINE_LR(FaustFactoryWord)
private:
    void fill_parameters(Stack& stack);

private:
    llvm_dsp_factory* factory_;
    dsp* dsp_;

    std::vector<FAUSTFLOAT *> values_;
    std::vector<Vec> outputs_;
};

}}
#endif
