/* ------------------------------------------------------------
name: "OsSquareF"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn OsSquareF -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __OsSquareF_H__
#define  __OsSquareF_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS OsSquareF
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

static float OsSquareF_faustpower2_f(float value) {
	return value * value;
}

class OsSquareF : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst1;
	int iVec0[2];
	float fRec0[2];
	float fVec1[2];
	int IOTA0;
	float fVec2[4096];
	float fConst2;
	float fConst3;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn OsSquareF -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "OsSquareF.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "OsSquareF");
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/sawN:author", "Julius O. Smith III");
		m->declare("oscillators.lib/sawN:license", "STK-4.3");
		m->declare("oscillators.lib/version", "0.3");
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
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 1.0f / fConst0;
		fConst2 = 0.5f * fConst0;
		fConst3 = 0.25f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fVec1[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 4096; l3 = l3 + 1) {
			fVec2[l3] = 0.0f;
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
	
	virtual OsSquareF* clone() {
		return new OsSquareF();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("OsSquareF");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = std::max<float>(float(input0[i0]), 23.44895f);
			float fTemp1 = std::max<float>(2e+01f, std::fabs(fTemp0));
			iVec0[0] = 1;
			float fTemp2 = fRec0[1] + fConst1 * fTemp1;
			fRec0[0] = fTemp2 - std::floor(fTemp2);
			float fTemp3 = OsSquareF_faustpower2_f(2.0f * fRec0[0] + -1.0f);
			fVec1[0] = fTemp3;
			float fTemp4 = float(iVec0[1]) * (fTemp3 - fVec1[1]) / fTemp1;
			fVec2[IOTA0 & 4095] = fTemp4;
			float fTemp5 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst2 / fTemp0));
			int iTemp6 = int(fTemp5);
			float fTemp7 = std::floor(fTemp5);
			output0[i0] = FAUSTFLOAT(fConst3 * (fTemp4 - fVec2[(IOTA0 - iTemp6) & 4095] * (fTemp7 + (1.0f - fTemp5)) - (fTemp5 - fTemp7) * fVec2[(IOTA0 - (iTemp6 + 1)) & 4095]));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fVec1[1] = fVec1[0];
			IOTA0 = IOTA0 + 1;
		}
	}

};

} // namespace mydsp

#endif
