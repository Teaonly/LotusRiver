/* ------------------------------------------------------------
name: "FiHighpass6e"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn FiHighpass6e -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FiHighpass6e_H__
#define  __FiHighpass6e_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS FiHighpass6e
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

static float FiHighpass6e_faustpower2_f(float value) {
	return value * value;
}

class FiHighpass6e : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fRec2[3];
	float fRec1[3];
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn FiHighpass6e -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "FiHighpass6e.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass6e:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass6e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highpass6e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "FiHighpass6e");
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
		fConst0 = 3.1415927f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 3; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
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
	
	virtual FiHighpass6e* clone() {
		return new FiHighpass6e();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FiHighpass6e");
		ui_interface->addNumEntry("fc", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::tan(fConst0 * float(fEntry0));
		float fSlow1 = FiHighpass6e_faustpower2_f(fSlow0);
		float fSlow2 = 1.0f / fSlow1;
		float fSlow3 = 2.0f * (0.9351402f - fSlow2);
		float fSlow4 = 1.0f / fSlow0;
		float fSlow5 = (fSlow4 + -0.15748216f) / fSlow0 + 0.9351402f;
		float fSlow6 = 1.0f / ((fSlow4 + 0.15748216f) / fSlow0 + 0.9351402f);
		float fSlow7 = 2.0f * (1.4500711f - fSlow2);
		float fSlow8 = (fSlow4 + -0.74313045f) / fSlow0 + 1.4500711f;
		float fSlow9 = 1.0f / ((fSlow4 + 0.74313045f) / fSlow0 + 1.4500711f);
		float fSlow10 = 2.0f * (4.0767817f - fSlow2);
		float fSlow11 = (fSlow4 + -3.1897273f) / fSlow0 + 4.0767817f;
		float fSlow12 = 1.0f / ((fSlow4 + 3.1897273f) / fSlow0 + 4.0767817f);
		float fSlow13 = 0.0017661728f / fSlow1;
		float fSlow14 = fSlow13 + 0.0004076782f;
		float fSlow15 = 2.0f * (0.0004076782f - fSlow13);
		float fSlow16 = 11.0520525f / fSlow1;
		float fSlow17 = fSlow16 + 1.4500711f;
		float fSlow18 = 2.0f * (1.4500711f - fSlow16);
		float fSlow19 = 50.06381f / fSlow1;
		float fSlow20 = fSlow19 + 0.9351402f;
		float fSlow21 = 2.0f * (0.9351402f - fSlow19);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec2[0] = float(input0[i0]) - fSlow12 * (fSlow11 * fRec2[2] + fSlow10 * fRec2[1]);
			fRec1[0] = fSlow12 * (fSlow14 * fRec2[0] + fSlow15 * fRec2[1] + fSlow14 * fRec2[2]) - fSlow9 * (fSlow8 * fRec1[2] + fSlow7 * fRec1[1]);
			fRec0[0] = fSlow9 * (fSlow17 * fRec1[0] + fSlow18 * fRec1[1] + fSlow17 * fRec1[2]) - fSlow6 * (fSlow5 * fRec0[2] + fSlow3 * fRec0[1]);
			output0[i0] = FAUSTFLOAT(fSlow6 * (fSlow20 * fRec0[0] + fSlow21 * fRec0[1] + fSlow20 * fRec0[2]));
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace mydsp

#endif
