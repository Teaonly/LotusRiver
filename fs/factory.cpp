#include <faust/dsp/llvm-dsp.h>
#include <faust/dsp/libfaust.h>

#include "fs/factory.hpp"
#include "fs/dsp.hpp"

namespace lr { namespace fs {
FaustFactoryWord::~FaustFactoryWord() {
    if ( dsp_ != nullptr) {
        delete dsp_;
    }
    if ( factory_ != nullptr) {
        deleteDSPFactory(factory_);
    }
}

void FaustFactoryWord::run(Stack& stack) {
    const std::string dspFile = stack.pop_string();
    const int sr = stack.pop_number();

    if ( factory_ == nullptr ) {
        std::string errMessage;
        const std::string jitTarget;

        factory_ = createDSPFactoryFromFile(dspFile, 0, nullptr, jitTarget, errMessage, -1);

        if ( factory_ == nullptr ) {
            std::cerr << "Can't create DSP factory, " << errMessage << std::endl;
            lr_panic("Creating DSP factory error!");
        }

        dsp_ = factory_->createDSPInstance();
        if ( !dsp_ ) {
            lr_panic("Can't create dsp instance from factory.");
        }
        dsp_->init(sr);

        // parameters
        mydsp::EasyUI ui;
        dsp_->buildUserInterface(&ui);
        for (size_t i = 0; i < ui.numValues(); i++) {
            values_.push_back( ui.value(i) );
        }

        // input & output
        for (int i = 0; i < dsp_->getNumOutputs(); i++) {
            outputs_.push_back( Vec() );
        }
    }

    const int ni = dsp_->getNumInputs();
    const int no = dsp_->getNumOutputs();

    // 0. zero input
    if ( ni == 0 ) {
        int bs = stack.pop_number();
        if ( outputs_[0].size() != bs ) {
            for (size_t i = 0; i < outputs_.size(); i++) {
                outputs_[i] = Vec::Zero(bs, 1);
            }
        }

        fill_parameters(stack);

        FAUSTFLOAT* dout[ no ];
        for (int i = 0; i < no; i++) {
            dout[i] = outputs_[i].data();
        }

        dsp_->compute(bs, nullptr, dout);

        if ( bs == 1 ) {
            for (int i = no - 1; i >= 0; i--) {
                stack.push_number( outputs_[i].data()[0] );
            }
            return;
        }

        for (int i = no - 1; i >= 0; i--) {
            stack.push_vector( &outputs_[i] );
        }
        return;
    }

    fill_parameters(stack);

    // 1. multiple signal input
    if ( stack.top().is_number() ) {
        FAUSTFLOAT din_[ni];
        FAUSTFLOAT* din[ni];

        for (int i =  0; i < ni; i++) {
            din_[i] = stack.pop_number();
            din[i] = &din_[i];
        }

        float* dout[no];
        for (int i =  0; i < no; i++) {
            if ( outputs_[i].size() != 1 ) {
                outputs_[i] = Vec::Zero(1, 1);
            }
            dout[i] = outputs_[i].data();
        }

        dsp_->compute(1, din, dout);

        for (int i = no - 1; i >= 0; i--) {
            stack.push_number( dout[i][0] );
        }
        return;
    }

    // 2. muliple vectout input
    {
        const Vec* din_[ni];
        float* din[ni];
        for (int i =  0; i < ni; i++) {
            din_[i] = stack.pop_vector();
            din[i] = const_cast<float *>(din_[i]->data());
        }

        float* dout[no];
        for (int i =  0; i < no; i++) {
            if ( outputs_[i].size() != din_[i]->size() ) {
                outputs_[i] = Vec::Zero(din_[i]->rows(), din_[i]->cols());
            }
            dout[i] = outputs_[i].data();
        }
        dsp_->compute(din_[0]->rows(), din, dout);

        for (int i = no - 1; i >= 0; i--) {
            stack.push_vector(&outputs_[i]);
        }
        return;
    }

}

void FaustFactoryWord::fill_parameters(Stack& stack) {
    auto params = stack.pop_number_list();
    for (size_t i = 0; i < params.size(); i++) {
        *values_[i] = params[i];
    }
}

}}
