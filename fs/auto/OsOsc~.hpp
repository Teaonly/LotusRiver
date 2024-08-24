/* ------------------------------------------------------------
name: "OsOsc"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn OsOsc -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __OsOsc_H__
#define  __OsOsc_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS OsOsc
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

class OsOscSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec0[2];
	
  public:
	
	int getNumInputsOsOscSIG0() {
		return 0;
	}
	int getNumOutputsOsOscSIG0() {
		return 1;
	}
	
	void instanceInitOsOscSIG0(int sample_rate) {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec0[l1] = 0;
		}
	}
	
	void fillOsOscSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec0[0] = 1;
			iRec0[0] = (iVec0[1] + iRec0[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec0[0]));
			iVec0[1] = iVec0[0];
			iRec0[1] = iRec0[0];
		}
	}

};

static OsOscSIG0* newOsOscSIG0() { return (OsOscSIG0*)new OsOscSIG0(); }
static void deleteOsOscSIG0(OsOscSIG0* dsp) { delete dsp; }

static float ftbl0OsOscSIG0[65536];

class OsOsc : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.9");
		m->declare("compile_options", "-lang cpp -light -cn OsOsc -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "OsOsc.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "OsOsc");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.3");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		OsOscSIG0* sig0 = newOsOscSIG0();
		sig0->instanceInitOsOscSIG0(sample_rate);
		sig0->fillOsOscSIG0(65536, ftbl0OsOscSIG0);
		deleteOsOscSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
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
	
	virtual OsOsc* clone() {
		return new OsOsc();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("OsOsc");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst0 * float(fEntry0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + (fRec1[1] - std::floor(fSlow0 + fRec1[1]));
			output0[i0] = FAUSTFLOAT(ftbl0OsOscSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec1[0]), 65535))]);
			fRec1[1] = fRec1[0];
		}
	}

};

} // namespace mydsp

#endif
