/* ------------------------------------------------------------
name: "FiBandpass6e"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn FiBandpass6e -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FiBandpass6e_H__
#define  __FiBandpass6e_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS FiBandpass6e
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

static float FiBandpass6e_faustpower2_f(float value) {
	return value * value;
}
static float FiBandpass6e_faustpower4_f(float value) {
	return value * value * value * value;
}
static float FiBandpass6e_faustpower3_f(float value) {
	return value * value * value;
}

class FiBandpass6e : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fEntry0;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec1[5];
	float fConst19;
	float fConst20;
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn FiBandpass6e -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "FiBandpass6e.dsp");
		m->declare("filters.lib/bandpass6e:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass6e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass6e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1sb:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1sb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1sb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2sb:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2sb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2sb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "FiBandpass6e");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.1415927f / fConst0;
		fConst2 = 4.0f * FiBandpass6e_faustpower2_f(fConst0);
		fConst3 = 0.5f / fConst0;
		fConst4 = 2.0f * fConst0;
		fConst5 = 1.6448919f / fConst0;
		float fConst6 = 1.0f / fConst0;
		fConst7 = FiBandpass6e_faustpower2_f(fConst6);
		fConst8 = 2.0f / fConst0;
		fConst9 = 2.0f * fConst7;
		fConst10 = FiBandpass6e_faustpower4_f(fConst6);
		float fConst11 = FiBandpass6e_faustpower3_f(fConst6);
		fConst12 = 1.6052735f * fConst11;
		fConst13 = 6.421094f / fConst0;
		fConst14 = 0.03961829f * fConst10;
		fConst15 = 3.210547f * fConst11;
		fConst16 = 12.842188f / fConst0;
		fConst17 = 4.0f * fConst10;
		fConst18 = 6.0f * fConst10;
		fConst19 = 0.07923658f * fConst10;
		fConst20 = 0.118854865f * fConst10;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 5; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
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
	
	virtual FiBandpass6e* clone() {
		return new FiBandpass6e();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FiBandpass6e");
		ui_interface->addNumEntry("fc", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst2 * std::tan(fConst1 * float(fEntry0));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = std::tan(fConst1 * float(input0[i0]));
			float fTemp1 = std::sqrt(fSlow0 * fTemp0);
			float fTemp2 = FiBandpass6e_faustpower2_f(fTemp1);
			float fTemp3 = fConst4 * fTemp0 - fConst3 * (fTemp2 / fTemp0);
			float fTemp4 = fConst5 * fTemp3;
			float fTemp5 = fConst7 * fTemp2;
			float fTemp6 = fTemp5 + fTemp4 + 4.0f;
			float fTemp7 = FiBandpass6e_faustpower2_f(fTemp3);
			float fTemp8 = FiBandpass6e_faustpower4_f(fTemp1);
			float fTemp9 = fConst10 * fTemp8 + fConst7 * (5.6490836f * fTemp7 + 8.0f * fTemp2);
			float fTemp10 = fConst13 + fConst12 * fTemp2;
			float fTemp11 = fTemp3 * fTemp10 + fTemp9 + 16.0f;
			float fTemp12 = fConst7 * (4.6460657f * fTemp7 + 0.15847316f * fTemp2);
			float fTemp13 = fConst15 * fTemp2;
			float fTemp14 = fConst17 * fTemp8;
			fRec1[0] = float(input1[i0]) - (fRec1[1] * (fTemp14 + fTemp3 * (fTemp13 - fConst16) + -64.0f) + fRec1[2] * (fConst18 * fTemp8 + fConst7 * (0.0f - (11.298167f * fTemp7 + 16.0f * fTemp2)) + 96.0f) + fRec1[3] * (fTemp14 + fTemp3 * (fConst16 - fTemp13) + -64.0f) + fRec1[4] * (fTemp9 + fTemp3 * (0.0f - fTemp10) + 16.0f)) / fTemp11;
			float fTemp15 = fConst19 * fTemp8 + -1.2677853f;
			fRec0[0] = (fRec1[0] * (fTemp12 + 0.31694633f) + fRec1[1] * fTemp15 + fRec1[2] * (fConst20 * fTemp8 + fConst7 * (0.0f - (9.292131f * fTemp7 + 0.31694633f * fTemp2)) + 1.9016778f) + fRec1[3] * fTemp15 + fRec1[4] * (fTemp12 + fConst14 * fTemp8 + 0.31694633f)) / fTemp11 - (fRec0[1] * (fConst9 * fTemp2 + -8.0f) + fRec0[2] * (fTemp5 + (4.0f - fTemp4))) / fTemp6;
			output0[i0] = FAUSTFLOAT(fConst8 * (fRec0[0] * fTemp3 / fTemp6) + fRec0[2] * (0.0f - fConst8 * (fTemp3 / fTemp6)));
			for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
				fRec1[j0] = fRec1[j0 - 1];
			}
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace mydsp

#endif
