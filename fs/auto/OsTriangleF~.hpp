/* ------------------------------------------------------------
name: "OsTriangleF"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn OsTriangleF -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __OsTriangleF_H__
#define  __OsTriangleF_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS OsTriangleF
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

static float OsTriangleF_faustpower2_f(float value) {
	return value * value;
}

class OsTriangleF : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst1;
	int iVec0[2];
	float fRec1[2];
	float fVec1[2];
	int IOTA0;
	float fVec2[4096];
	float fConst2;
	float fConst3;
	float fRec0[2];
	float fConst4;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn OsTriangleF -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "OsTriangleF.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "OsTriangleF");
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
		fConst4 = 4.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fVec1[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 4096; l3 = l3 + 1) {
			fVec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec0[l4] = 0.0f;
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
	
	virtual OsTriangleF* clone() {
		return new OsTriangleF();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("OsTriangleF");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			float fTemp1 = std::max<float>(fTemp0, 23.44895f);
			float fTemp2 = std::max<float>(2e+01f, std::fabs(fTemp1));
			iVec0[0] = 1;
			float fTemp3 = fRec1[1] + fConst1 * fTemp2;
			fRec1[0] = fTemp3 - std::floor(fTemp3);
			float fTemp4 = OsTriangleF_faustpower2_f(2.0f * fRec1[0] + -1.0f);
			fVec1[0] = fTemp4;
			float fTemp5 = float(iVec0[1]) * (fTemp4 - fVec1[1]) / fTemp2;
			fVec2[IOTA0 & 4095] = fTemp5;
			float fTemp6 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst2 / fTemp1));
			int iTemp7 = int(fTemp6);
			float fTemp8 = std::floor(fTemp6);
			fRec0[0] = 0.999f * fRec0[1] + fConst3 * (fTemp5 - fVec2[(IOTA0 - iTemp7) & 4095] * (fTemp8 + (1.0f - fTemp6)) - (fTemp6 - fTemp8) * fVec2[(IOTA0 - (iTemp7 + 1)) & 4095]);
			output0[i0] = FAUSTFLOAT(fConst4 * fTemp0 * fRec0[0]);
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			IOTA0 = IOTA0 + 1;
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace mydsp

#endif
