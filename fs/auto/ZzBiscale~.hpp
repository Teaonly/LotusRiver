/* ------------------------------------------------------------
name: "biscale"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn ZzBiscale -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ZzBiscale_H__
#define  __ZzBiscale_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS ZzBiscale
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


class ZzBiscale : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn ZzBiscale -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "biscale.dsp");
		m->declare("name", "biscale");
	}

	virtual int getNumInputs() {
		return 1;
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
		fEntry0 = FAUSTFLOAT(0.1f);
		fEntry1 = FAUSTFLOAT(0.1f);
	}
	
	virtual void instanceClear() {
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
	
	virtual ZzBiscale* clone() {
		return new ZzBiscale();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("biscale");
		ui_interface->addNumEntry("low", &fEntry0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("up", &fEntry1, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fEntry0);
		float fSlow1 = 0.5f * (float(fEntry1) - fSlow0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			output0[i0] = FAUSTFLOAT(fSlow0 + fSlow1 * (float(fTemp0 > 1.0f) + fTemp0 * float((fTemp0 <= 1.0f) & (fTemp0 >= -1.0f)) + (1.0f - float(fTemp0 < -1.0f))));
		}
	}

};

} // namespace mydsp

#endif
