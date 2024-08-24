/* ------------------------------------------------------------
name: "tenvx"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn ZzTenvx -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ZzTenvx_H__
#define  __ZzTenvx_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS ZzTenvx
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


class ZzTenvx : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fRec1[2];
	FAUSTFLOAT fEntry1;
	float fConst1;
	FAUSTFLOAT fEntry2;
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn ZzTenvx -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "tenvx.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "tenvx");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 1.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.1f);
		fEntry1 = FAUSTFLOAT(0.1f);
		fEntry2 = FAUSTFLOAT(0.1f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
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
	
	virtual ZzTenvx* clone() {
		return new ZzTenvx();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("tenvx");
		ui_interface->addNumEntry("atk", &fEntry2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("hold", &fEntry0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("rel", &fEntry1, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst0 * float(fEntry0);
		float fSlow1 = std::exp(0.0f - fConst1 / float(fEntry1));
		float fSlow2 = std::exp(0.0f - fConst1 / float(fEntry2));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			fRec1[0] = fSlow0 * float(fTemp0 != 0.0f) + float(fTemp0 == 0.0f) * (fRec1[1] * float(fRec1[1] > 0.0f) + -1.0f);
			fRec0[0] = float(fRec1[0] > 0.0f) * (1.0f - fSlow2 * (1.0f - fRec0[1])) + fSlow1 * float(fRec1[0] <= 0.0f) * fRec0[1];
			output0[i0] = FAUSTFLOAT(fRec0[0]);
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace mydsp

#endif
