/* ------------------------------------------------------------
name: "FiHighpass3e"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn FiHighpass3e -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FiHighpass3e_H__
#define  __FiHighpass3e_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS FiHighpass3e
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

static float FiHighpass3e_faustpower2_f(float value) {
	return value * value;
}

class FiHighpass3e : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fRec1[3];
	float fVec0[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn FiHighpass3e -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "FiHighpass3e.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass3e:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass3e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highpass3e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
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
		m->declare("name", "FiHighpass3e");
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
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
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
	
	virtual FiHighpass3e* clone() {
		return new FiHighpass3e();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FiHighpass3e");
		ui_interface->addNumEntry("fc", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::tan(fConst0 * float(fEntry0));
		float fSlow1 = 1.0f / fSlow0;
		float fSlow2 = 1.2158854f - fSlow1;
		float fSlow3 = FiHighpass3e_faustpower2_f(fSlow0);
		float fSlow4 = 2.0f * (0.70807946f - 1.0f / fSlow3);
		float fSlow5 = (fSlow1 + -0.5683306f) / fSlow0 + 0.70807946f;
		float fSlow6 = (fSlow1 + 0.5683306f) / fSlow0 + 0.70807946f;
		float fSlow7 = 1.0f / fSlow6;
		float fSlow8 = 0.8224459f / fSlow3;
		float fSlow9 = fSlow8 + 0.014026448f;
		float fSlow10 = 2.0f * (0.014026448f - fSlow8);
		float fSlow11 = 1.2158854f / (fSlow0 * fSlow6);
		float fSlow12 = fSlow1 + 1.2158854f;
		float fSlow13 = 1.0f / fSlow12;
		float fSlow14 = 0.0f - 1.2158854f / (fSlow0 * fSlow12);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = float(input0[i0]) - fSlow7 * (fSlow5 * fRec1[2] + fSlow4 * fRec1[1]);
			float fTemp0 = fSlow9 * fRec1[0] + fSlow10 * fRec1[1] + fSlow9 * fRec1[2];
			fVec0[0] = fSlow7 * fTemp0;
			fRec0[0] = fSlow14 * fVec0[1] + fSlow13 * (fSlow11 * fTemp0 - fSlow2 * fRec0[1]);
			output0[i0] = FAUSTFLOAT(fRec0[0]);
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace mydsp

#endif
