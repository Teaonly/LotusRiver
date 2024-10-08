/* ------------------------------------------------------------
name: "NoNoise"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -lang cpp -light -cn NoNoise -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __NoNoise_H__
#define  __NoNoise_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace mydsp {

#ifndef FAUSTCLASS 
#define FAUSTCLASS NoNoise
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


class NoNoise : public dsp {
	
 private:
	
	int iRec0[2];
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -light -cn NoNoise -es 1 -mcd 16 -single -ftz 0");
		m->declare("filename", "NoNoise.dsp");
		m->declare("name", "NoNoise");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.4");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec0[l0] = 0;
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
	
	virtual NoNoise* clone() {
		return new NoNoise();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("NoNoise");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec0[0] = 1103515245 * iRec0[1] + 12345;
			output0[i0] = FAUSTFLOAT(4.656613e-10f * float(iRec0[0]));
			iRec0[1] = iRec0[0];
		}
	}

};

} // namespace mydsp

#endif
