/* ------------------------------------------------------------
name: "FiBandpass"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn FiBandpass -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FiBandpass_H__
#define  __FiBandpass_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS FiBandpass
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

static float FiBandpass_faustpower2_f(float value) {
	return value * value;
}
static float FiBandpass_faustpower3_f(float value) {
	return value * value * value;
}
static float FiBandpass_faustpower4_f(float value) {
	return value * value * value * value;
}

class FiBandpass : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fEntry1;
	float fConst2;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec0[5];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn FiBandpass -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "FiBandpass.dsp");
		m->declare("filters.lib/bandpass0_bandstop1:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass0_bandstop1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass0_bandstop1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/bandpass:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2sb:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2sb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2sb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "FiBandpass");
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
		fConst1 = 3.1415927f / fConst0;
		fConst2 = 4.0f * FiBandpass_faustpower2_f(fConst0);
		float fConst3 = 1.0f / fConst0;
		float fConst4 = FiBandpass_faustpower3_f(fConst3);
		fConst5 = 2.828427f * fConst4;
		fConst6 = 11.313708f / fConst0;
		fConst7 = 0.5f / fConst0;
		fConst8 = 2.0f * fConst0;
		fConst9 = FiBandpass_faustpower2_f(fConst3);
		fConst10 = FiBandpass_faustpower4_f(fConst3);
		fConst11 = 5.656854f * fConst4;
		fConst12 = 22.627417f / fConst0;
		fConst13 = 4.0f * fConst10;
		fConst14 = 6.0f * fConst10;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 5; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
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
	
	virtual FiBandpass* clone() {
		return new FiBandpass();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FiBandpass");
		ui_interface->addNumEntry("fl", &fEntry1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addNumEntry("fu", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::tan(fConst1 * float(fEntry0));
		float fSlow1 = std::sqrt(fConst2 * std::tan(fConst1 * float(fEntry1)) * fSlow0);
		float fSlow2 = FiBandpass_faustpower2_f(fSlow1);
		float fSlow3 = fConst6 + fConst5 * fSlow2;
		float fSlow4 = fConst8 * fSlow0 - fConst7 * (fSlow2 / fSlow0);
		float fSlow5 = FiBandpass_faustpower2_f(fSlow4);
		float fSlow6 = 4.0f * fSlow5;
		float fSlow7 = FiBandpass_faustpower4_f(fSlow1);
		float fSlow8 = fConst10 * fSlow7 + fConst9 * (fSlow6 + 8.0f * fSlow2);
		float fSlow9 = fSlow8 + fSlow4 * (0.0f - fSlow3) + 16.0f;
		float fSlow10 = fConst11 * fSlow2;
		float fSlow11 = fConst13 * fSlow7;
		float fSlow12 = fSlow11 + fSlow4 * (fConst12 - fSlow10) + -64.0f;
		float fSlow13 = 8.0f * fSlow5;
		float fSlow14 = fConst14 * fSlow7 + fConst9 * (0.0f - (fSlow13 + 16.0f * fSlow2)) + 96.0f;
		float fSlow15 = fSlow11 + fSlow4 * (fSlow10 - fConst12) + -64.0f;
		float fSlow16 = fSlow4 * fSlow3 + fSlow8 + 16.0f;
		float fSlow17 = 1.0f / fSlow16;
		float fSlow18 = 0.0f - fSlow13;
		float fSlow19 = fConst9 / fSlow16;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = float(input0[i0]) - fSlow17 * (fSlow15 * fRec0[1] + fSlow14 * fRec0[2] + fSlow12 * fRec0[3] + fSlow9 * fRec0[4]);
			output0[i0] = FAUSTFLOAT(fSlow19 * (fSlow18 * fRec0[2] + fSlow6 * fRec0[0] + fSlow6 * fRec0[4]));
			for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
				fRec0[j0] = fRec0[j0 - 1];
			}
		}
	}

};

} // namespace mydsp

#endif
