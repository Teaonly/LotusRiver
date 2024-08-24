/* ------------------------------------------------------------
name: "fm"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn ZzFm -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ZzFm_H__
#define  __ZzFm_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS ZzFm
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

class ZzFmSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec0[2];
	
  public:
	
	int getNumInputsZzFmSIG0() {
		return 0;
	}
	int getNumOutputsZzFmSIG0() {
		return 1;
	}
	
	void instanceInitZzFmSIG0(int sample_rate) {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec0[l1] = 0;
		}
	}
	
	void fillZzFmSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec0[0] = 1;
			iRec0[0] = (iVec0[1] + iRec0[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec0[0]));
			iVec0[1] = iVec0[0];
			iRec0[1] = iRec0[0];
		}
	}

};

static ZzFmSIG0* newZzFmSIG0() { return (ZzFmSIG0*)new ZzFmSIG0(); }
static void deleteZzFmSIG0(ZzFmSIG0* dsp) { delete dsp; }

static float ftbl0ZzFmSIG0[65536];

class ZzFm : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fRec2[2];
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fEntry2;
	float fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.9");
		m->declare("compile_options", "-lang cpp -light -cn ZzFm -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "fm.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "fm");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.3");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
		m->declare("synths.lib/fm:author", "Romain Michon");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "0.1");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		ZzFmSIG0* sig0 = newZzFmSIG0();
		sig0->instanceInitZzFmSIG0(sample_rate);
		sig0->fillZzFmSIG0(65536, ftbl0ZzFmSIG0);
		deleteZzFmSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.1f);
		fEntry1 = FAUSTFLOAT(0.1f);
		fEntry2 = FAUSTFLOAT(0.1f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
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
	
	virtual ZzFm* clone() {
		return new ZzFm();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("fm");
		ui_interface->addNumEntry("carry", &fEntry2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("index", &fEntry1, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("modulator", &fEntry0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst0 * float(fEntry0);
		float fSlow1 = float(fEntry1);
		float fSlow2 = float(fEntry2);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec2[0] = fSlow0 + (fRec2[1] - std::floor(fSlow0 + fRec2[1]));
			float fTemp0 = fRec1[1] + fConst0 * (fSlow2 + fSlow1 * ftbl0ZzFmSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec2[0]), 65535))]);
			fRec1[0] = fTemp0 - std::floor(fTemp0);
			output0[i0] = FAUSTFLOAT(ftbl0ZzFmSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec1[0]), 65535))]);
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}

};

} // namespace mydsp

#endif
