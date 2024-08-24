/* ------------------------------------------------------------
name: "BaBitcrusher"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn BaBitcrusher -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __BaBitcrusher_H__
#define  __BaBitcrusher_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS BaBitcrusher
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


class BaBitcrusher : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/bitcrusher:author", "Julius O. Smith III, revised by Stephane Letz");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.9");
		m->declare("compile_options", "-lang cpp -light -cn BaBitcrusher -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "BaBitcrusher.dsp");
		m->declare("name", "BaBitcrusher");
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
		fEntry0 = FAUSTFLOAT(0.0f);
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
	
	virtual BaBitcrusher* clone() {
		return new BaBitcrusher();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("BaBitcrusher");
		ui_interface->addNumEntry("nbits", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::pow(2.0f, float(fEntry0)) + -1.0f;
		float fSlow1 = 1.0f / fSlow0;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			output0[i0] = FAUSTFLOAT(fSlow1 * std::floor(fSlow0 * float(input0[i0]) + 0.5f));
		}
	}

};

} // namespace mydsp

#endif
