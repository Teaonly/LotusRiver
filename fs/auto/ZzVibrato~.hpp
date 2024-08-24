/* ------------------------------------------------------------
name: "vibrato"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn ZzVibrato -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ZzVibrato_H__
#define  __ZzVibrato_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS ZzVibrato
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

class ZzVibratoSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec0[2];
	
  public:
	
	int getNumInputsZzVibratoSIG0() {
		return 0;
	}
	int getNumOutputsZzVibratoSIG0() {
		return 1;
	}
	
	void instanceInitZzVibratoSIG0(int sample_rate) {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec0[l1] = 0;
		}
	}
	
	void fillZzVibratoSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec0[0] = 1;
			iRec0[0] = (iVec0[1] + iRec0[1]) % 65536;
			table[i1] = std::cos(9.58738e-05f * float(iRec0[0]));
			iVec0[1] = iVec0[0];
			iRec0[1] = iRec0[0];
		}
	}

};

static ZzVibratoSIG0* newZzVibratoSIG0() { return (ZzVibratoSIG0*)new ZzVibratoSIG0(); }
static void deleteZzVibratoSIG0(ZzVibratoSIG0* dsp) { delete dsp; }

class ZzVibratoSIG1 {
	
  private:
	
	int iVec1[2];
	int iRec2[2];
	
  public:
	
	int getNumInputsZzVibratoSIG1() {
		return 0;
	}
	int getNumOutputsZzVibratoSIG1() {
		return 1;
	}
	
	void instanceInitZzVibratoSIG1(int sample_rate) {
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iVec1[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec2[l4] = 0;
		}
	}
	
	void fillZzVibratoSIG1(int count, float* table) {
		for (int i2 = 0; i2 < count; i2 = i2 + 1) {
			iVec1[0] = 1;
			iRec2[0] = (iVec1[1] + iRec2[1]) % 65536;
			table[i2] = std::sin(9.58738e-05f * float(iRec2[0]));
			iVec1[1] = iVec1[0];
			iRec2[1] = iRec2[0];
		}
	}

};

static ZzVibratoSIG1* newZzVibratoSIG1() { return (ZzVibratoSIG1*)new ZzVibratoSIG1(); }
static void deleteZzVibratoSIG1(ZzVibratoSIG1* dsp) { delete dsp; }

static float ftbl0ZzVibratoSIG0[65536];
static float ftbl1ZzVibratoSIG1[65536];

class ZzVibrato : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fRec1[2];
	FAUSTFLOAT fEntry1;
	int iRec3[2];
	int iRec4[2];
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fEntry3;
	float fConst2;
	float fConst3;
	float fRec5[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.9");
		m->declare("compile_options", "-lang cpp -light -cn ZzVibrato -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "vibrato.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "vibrato");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
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
		ZzVibratoSIG0* sig0 = newZzVibratoSIG0();
		sig0->instanceInitZzVibratoSIG0(sample_rate);
		sig0->fillZzVibratoSIG0(65536, ftbl0ZzVibratoSIG0);
		ZzVibratoSIG1* sig1 = newZzVibratoSIG1();
		sig1->instanceInitZzVibratoSIG1(sample_rate);
		sig1->fillZzVibratoSIG1(65536, ftbl1ZzVibratoSIG1);
		deleteZzVibratoSIG0(sig0);
		deleteZzVibratoSIG1(sig1);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 1.0f / fConst0;
		fConst2 = 0.2f * fConst0;
		fConst3 = 0.8f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.1f);
		fEntry1 = FAUSTFLOAT(0.1f);
		fEntry2 = FAUSTFLOAT(0.1f);
		fEntry3 = FAUSTFLOAT(0.1f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec3[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec4[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec5[l7] = 0.0f;
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
	
	virtual ZzVibrato* clone() {
		return new ZzVibrato();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("vibrato");
		ui_interface->addNumEntry("attack", &fEntry3, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("phase", &fEntry1, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("release", &fEntry2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst1 * float(fEntry0);
		float fSlow1 = float(fEntry1);
		float fSlow2 = std::sin(fSlow1);
		float fSlow3 = std::cos(fSlow1);
		float fSlow4 = float(fEntry2);
		float fSlow5 = 1.0f - 1.0f / std::pow(6e+04f, 1.0f / (float(fSlow4 == 0.0f) + fConst0 * fSlow4));
		float fSlow6 = float(fEntry3);
		float fSlow7 = fConst2 * fSlow6;
		float fSlow8 = float((0.2f * fSlow6) == 0.0f) + fSlow7;
		float fSlow9 = 0.6f / (float((0.8f * fSlow6) == 0.0f) + fConst3 * fSlow6);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + (fRec1[1] - std::floor(fSlow0 + fRec1[1]));
			int iTemp0 = std::max<int>(0, std::min<int>(int(65536.0f * fRec1[0]), 65535));
			float fTemp1 = float(input0[i0]);
			int iTemp2 = fTemp1 > 0.0f;
			iRec3[0] = iTemp2 & (iRec3[1] | (fRec5[1] >= 1.0f));
			iRec4[0] = iTemp2 * (iRec4[1] + 1);
			int iTemp3 = (fTemp1 <= 0.0f) & (fRec5[1] > 0.0f);
			float fTemp4 = float(iRec4[1]);
			fRec5[0] = (fSlow9 * float(((((iRec3[1] == 0) & iTemp2) & (fRec5[1] < 1.0f)) & (fTemp4 > fSlow7)) * (1 - (fTemp4 < fSlow8))) + fRec5[1] * (1.0f - fSlow5 * float(iTemp3))) * float((iTemp3 == 0) | (fRec5[1] >= 1e-06f));
			output0[i0] = FAUSTFLOAT(fRec5[0] * (fSlow3 * ftbl1ZzVibratoSIG1[iTemp0] + fSlow2 * ftbl0ZzVibratoSIG0[iTemp0]));
			fRec1[1] = fRec1[0];
			iRec3[1] = iRec3[0];
			iRec4[1] = iRec4[0];
			fRec5[1] = fRec5[0];
		}
	}

};

} // namespace mydsp

#endif
