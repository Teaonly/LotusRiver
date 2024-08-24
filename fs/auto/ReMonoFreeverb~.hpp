/* ------------------------------------------------------------
name: "ReMonoFreeverb"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn ReMonoFreeverb -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __ReMonoFreeverb_H__
#define  __ReMonoFreeverb_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS ReMonoFreeverb
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


class ReMonoFreeverb : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	float fRec9[2];
	FAUSTFLOAT fEntry2;
	int IOTA0;
	float fVec0[8192];
	FAUSTFLOAT fEntry3;
	int fSampleRate;
	float fConst1;
	float fRec8[2];
	float fRec11[2];
	float fVec1[8192];
	float fConst2;
	float fRec10[2];
	float fRec13[2];
	float fVec2[8192];
	float fConst3;
	float fRec12[2];
	float fRec15[2];
	float fVec3[8192];
	float fConst4;
	float fRec14[2];
	float fRec17[2];
	float fVec4[8192];
	float fConst5;
	float fRec16[2];
	float fRec19[2];
	float fVec5[8192];
	float fConst6;
	float fRec18[2];
	float fRec21[2];
	float fVec6[8192];
	float fConst7;
	float fRec20[2];
	float fRec23[2];
	float fVec7[8192];
	float fConst8;
	float fRec22[2];
	float fVec8[2048];
	float fConst9;
	float fRec6[2];
	float fVec9[2048];
	float fConst10;
	float fRec4[2];
	float fVec10[2048];
	float fConst11;
	float fRec2[2];
	float fVec11[1024];
	float fConst12;
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn ReMonoFreeverb -es 1 -mcd 16 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "ReMonoFreeverb.dsp");
		m->declare("filters.lib/allpass_comb:author", "Julius O. Smith III");
		m->declare("filters.lib/allpass_comb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpass_comb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "ReMonoFreeverb");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
		m->declare("reverbs.lib/mono_freeverb:author", "Romain Michon");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.2");
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
		fConst1 = float(int(0.036666665f * fConst0));
		fConst2 = float(int(0.035306122f * fConst0));
		fConst3 = float(int(0.033809524f * fConst0));
		fConst4 = float(int(0.0322449f * fConst0));
		fConst5 = float(int(0.030748298f * fConst0));
		fConst6 = float(int(0.028956916f * fConst0));
		fConst7 = float(int(0.026938776f * fConst0));
		fConst8 = float(int(0.025306122f * fConst0));
		fConst9 = float(int(0.0126077095f * fConst0));
		fConst10 = float(int(0.01f * fConst0));
		fConst11 = float(int(0.0077324263f * fConst0));
		fConst12 = float(int(0.0051020407f * fConst0));
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(0.0f);
		fEntry2 = FAUSTFLOAT(0.0f);
		fEntry3 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec9[l0] = 0.0f;
		}
		IOTA0 = 0;
		for (int l1 = 0; l1 < 8192; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec8[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec11[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 8192; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec10[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec13[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 8192; l7 = l7 + 1) {
			fVec2[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec12[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec15[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 8192; l10 = l10 + 1) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec14[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec17[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 8192; l13 = l13 + 1) {
			fVec4[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec16[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec19[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 8192; l16 = l16 + 1) {
			fVec5[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec18[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec21[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 8192; l19 = l19 + 1) {
			fVec6[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec20[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec23[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 8192; l22 = l22 + 1) {
			fVec7[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec22[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2048; l24 = l24 + 1) {
			fVec8[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec6[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2048; l26 = l26 + 1) {
			fVec9[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec4[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2048; l28 = l28 + 1) {
			fVec10[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec2[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 1024; l30 = l30 + 1) {
			fVec11[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec0[l31] = 0.0f;
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
	
	virtual ReMonoFreeverb* clone() {
		return new ReMonoFreeverb();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("ReMonoFreeverb");
		ui_interface->addNumEntry("damp", &fEntry1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addNumEntry("fb1", &fEntry2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addNumEntry("fb2", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addNumEntry("spread", &fEntry3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fEntry0);
		float fSlow1 = float(fEntry1);
		float fSlow2 = 1.0f - fSlow1;
		float fSlow3 = float(fEntry2);
		float fSlow4 = float(fEntry3);
		int iSlow5 = int(fConst1 + fSlow4);
		int iSlow6 = int(fConst2 + fSlow4);
		int iSlow7 = int(fConst3 + fSlow4);
		int iSlow8 = int(fConst4 + fSlow4);
		int iSlow9 = int(fConst5 + fSlow4);
		int iSlow10 = int(fConst6 + fSlow4);
		int iSlow11 = int(fConst7 + fSlow4);
		int iSlow12 = int(fConst8 + fSlow4);
		float fSlow13 = fSlow4 + -1.0f;
		int iSlow14 = int(std::min<float>(1024.0f, std::max<float>(0.0f, fConst9 + fSlow13)));
		int iSlow15 = int(std::min<float>(1024.0f, std::max<float>(0.0f, fConst10 + fSlow13)));
		int iSlow16 = int(std::min<float>(1024.0f, std::max<float>(0.0f, fConst11 + fSlow13)));
		int iSlow17 = int(std::min<float>(1024.0f, std::max<float>(0.0f, fConst12 + fSlow13)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec9[0] = fSlow1 * fRec9[1] + fSlow2 * fRec8[1];
			float fTemp0 = float(input0[i0]);
			fVec0[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec9[0];
			fRec8[0] = fVec0[(IOTA0 - iSlow5) & 8191];
			fRec11[0] = fSlow1 * fRec11[1] + fSlow2 * fRec10[1];
			fVec1[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec11[0];
			fRec10[0] = fVec1[(IOTA0 - iSlow6) & 8191];
			fRec13[0] = fSlow1 * fRec13[1] + fSlow2 * fRec12[1];
			fVec2[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec13[0];
			fRec12[0] = fVec2[(IOTA0 - iSlow7) & 8191];
			fRec15[0] = fSlow1 * fRec15[1] + fSlow2 * fRec14[1];
			fVec3[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec15[0];
			fRec14[0] = fVec3[(IOTA0 - iSlow8) & 8191];
			fRec17[0] = fSlow1 * fRec17[1] + fSlow2 * fRec16[1];
			fVec4[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec17[0];
			fRec16[0] = fVec4[(IOTA0 - iSlow9) & 8191];
			fRec19[0] = fSlow1 * fRec19[1] + fSlow2 * fRec18[1];
			fVec5[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec19[0];
			fRec18[0] = fVec5[(IOTA0 - iSlow10) & 8191];
			fRec21[0] = fSlow1 * fRec21[1] + fSlow2 * fRec20[1];
			fVec6[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec21[0];
			fRec20[0] = fVec6[(IOTA0 - iSlow11) & 8191];
			fRec23[0] = fSlow1 * fRec23[1] + fSlow2 * fRec22[1];
			fVec7[IOTA0 & 8191] = fTemp0 + fSlow3 * fRec23[0];
			fRec22[0] = fVec7[(IOTA0 - iSlow12) & 8191];
			float fTemp1 = fRec22[0] + fRec20[0] + fRec18[0] + fRec16[0] + fRec14[0] + fRec12[0] + fRec10[0] + fRec8[0] + fSlow0 * fRec6[1];
			fVec8[IOTA0 & 2047] = fTemp1;
			fRec6[0] = fVec8[(IOTA0 - iSlow14) & 2047];
			float fRec7 = 0.0f - fSlow0 * fTemp1;
			float fTemp2 = fRec6[1] + fRec7 + fSlow0 * fRec4[1];
			fVec9[IOTA0 & 2047] = fTemp2;
			fRec4[0] = fVec9[(IOTA0 - iSlow15) & 2047];
			float fRec5 = 0.0f - fSlow0 * fTemp2;
			float fTemp3 = fRec4[1] + fRec5 + fSlow0 * fRec2[1];
			fVec10[IOTA0 & 2047] = fTemp3;
			fRec2[0] = fVec10[(IOTA0 - iSlow16) & 2047];
			float fRec3 = 0.0f - fSlow0 * fTemp3;
			float fTemp4 = fRec2[1] + fRec3 + fSlow0 * fRec0[1];
			fVec11[IOTA0 & 1023] = fTemp4;
			fRec0[0] = fVec11[(IOTA0 - iSlow17) & 1023];
			float fRec1 = 0.0f - fSlow0 * fTemp4;
			output0[i0] = FAUSTFLOAT(fRec1 + fRec0[1]);
			fRec9[1] = fRec9[0];
			IOTA0 = IOTA0 + 1;
			fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace mydsp

#endif
