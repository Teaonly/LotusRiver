#include "lr.hpp"

#include "fs/dsp.hpp"
#include "fs/auto/NoNoise~.hpp"
#include "fs/auto/NoNoise.hpp"

namespace lr { namespace fs {

NoNoiseWord::~NoNoiseWord() {
    if ( dsp != nullptr ) {
        delete dsp;
    }
}

void NoNoiseWord::run(Stack& stack) {
    const int nInput = 0;
    
    int sr = stack.pop_number();
    int bs = -1;
    if ( nInput == 0 ) {
        bs = stack.pop_number();
    }
    
    if ( dsp == nullptr ) {
        mydsp::EasyUI ui;
       
        dsp = new mydsp::NoNoise();
        dsp->init(sr);
        dsp->buildUserInterface(&ui);

        // init parameters

    }
    
    // load parameters

    
    
    if ( nInput == 0 ) {
        none_input(bs, stack);
        return;
    }

    if ( stack.top().is_number() ) {
        signals_input(stack);
        return;
    }
    
    vectors_input(stack);
    return;
}

void NoNoiseWord::none_input(const int bs, Stack& stack) {
    float* dout[1];

    for (int i =  0; i < 1; i++) {
        if ( outputs_[i].size() != bs ) {
            outputs_[i] = Vec::Zero(bs, 1);
        }
        dout[i] = outputs_[i].data();
    }
    
    dsp->compute(bs, nullptr, dout);

    if ( bs == 1 ) {
        for (int i = 1 - 1; i >= 0; i--) {
            stack.push_number( outputs_[i].data()[0] );
        }
        return;
    }
    
    for (int i = 1 - 1; i >= 0; i--) {
        stack.push_vector( &outputs_[i] );
    }
}

void NoNoiseWord::signals_input(Stack& stack) {
    float din_[0];
    float* din[0];

    for (int i =  0; i < 0; i++) {
        din_[i] = stack.pop_number();
        din[i] = &din_[i];
    }

    float* dout[1];
    for (int i =  0; i < 1; i++) {
        if ( outputs_[i].size() != 1 ) {
            outputs_[i] = Vec::Zero(1, 1);
        }
        dout[i] = outputs_[i].data();
    }
    
    dsp->compute(1, din, dout);
    
    for (int i = 1 - 1; i >= 0; i--) {
        stack.push_number( dout[i][0] );
    }
}

void NoNoiseWord::vectors_input(Stack& stack) {
    const Vec* din_[0];
    float* din[0];
    for (int i =  0; i < 0; i++) {
        din_[i] = stack.pop_vector();
        din[i] = const_cast<float *>(din_[i]->data());
    }

    float* dout[1];
    for (int i =  0; i < 1; i++) {
        if ( outputs_[i].size() != din_[i]->size() ) {
            outputs_[i] = Vec::Zero(din_[i]->rows(), din_[i]->cols());
        }
        dout[i] = outputs_[i].data();
    }
    dsp->compute(din_[0]->rows(), din, dout);
    
    for (int i = 1 - 1; i >= 0; i--) {
        stack.push_vector(&outputs_[i]);
    }
}


}}

