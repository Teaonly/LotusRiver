#include "lr.hpp"

#include "fs/dsp.hpp"
#include "fs/auto/ZzVibrato~.hpp"
#include "fs/auto/ZzVibrato.hpp"

namespace lr { namespace fs {

ZzVibratoWord::~ZzVibratoWord() {
    if ( dsp != nullptr ) {
        delete dsp;
    }
}

void ZzVibratoWord::run(Stack& stack) {
    const int nInput = 1;
    
    int sr = stack.pop_number();
    int bs = -1;
    if ( nInput == 0 ) {
        bs = stack.pop_number();
    }
    
    if ( dsp == nullptr ) {
        mydsp::EasyUI ui;
       
        dsp = new mydsp::ZzVibrato();
        dsp->init(sr);
        dsp->buildUserInterface(&ui);

        // init parameters
        release_ = ui.value("release");
        attack_ = ui.value("attack");
        phase_ = ui.value("phase");
        freq_ = ui.value("freq");

    }
    
    // load parameters
    *release_ = stack.pop_number();
    *attack_ = stack.pop_number();
    *phase_ = stack.pop_number();
    *freq_ = stack.pop_number();

    
    
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

void ZzVibratoWord::none_input(const int bs, Stack& stack) {
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

void ZzVibratoWord::signals_input(Stack& stack) {
    float din_[1];
    float* din[1];

    for (int i =  0; i < 1; i++) {
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

void ZzVibratoWord::vectors_input(Stack& stack) {
    const Vec* din_[1];
    float* din[1];
    for (int i =  0; i < 1; i++) {
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

