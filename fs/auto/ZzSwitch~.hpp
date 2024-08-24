/* ------------------------------------------------------------
name: "switch"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn ZzSwitch -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ZzSwitch_H__
#define  __ZzSwitch_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS ZzSwitch
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class ZzSwitch : public dsp {
	
 private:
	
	int iRec0[2];
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn ZzSwitch -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "switch.dsp");
		m->declare("name", "switch");
	}

	virtual int getNumInputs() {
		return 3;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec0[l0] = 0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual ZzSwitch* clone() {
		return new ZzSwitch();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("switch");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input2[i0]);
			iRec0[0] = (fTemp0 == 0.0f) * iRec0[1] + (fTemp0 != 0.0f) * (1 - iRec0[1]);
			output0[i0] = FAUSTFLOAT(float(input0[i0]) * float(iRec0[0] != 0) + float(input1[i0]) * float(iRec0[0] == 0));
			iRec0[1] = iRec0[0];
		}
	}

};

} // namespace mydsp

#endif
