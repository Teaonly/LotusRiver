#  1     2       3         4          5 
# input, output, dsp_name, dsp_class, [parameters]
define auto2hpp
	./gen_dsp $(3) $(5) > auto/$(4).dsp 
	faust -light -o auto/$(4)~.hpp -ns mydsp -cn $(4) auto/$(4).dsp
	./gen_hpp $(2) $(4) $(5) > auto/$(4).hpp
	./gen_cpp $(1) $(2) $(4) $(5) > auto/$(4).cpp
endef

define dsp2hpp
	faust -light -o auto/$(4)~.hpp -ns mydsp -cn $(4) zz/$(3).dsp
	./gen_hpp $(2) $(4) $(5) > auto/$(4).hpp
	./gen_cpp $(1) $(2) $(4) $(5) > auto/$(4).cpp
endef


gen_dsp: gen_tools/gen_dsp.cpp
	g++ -o $@ gen_tools/gen_dsp.cpp

gen_hpp: gen_tools/gen_hpp.cpp
	g++ -o $@ gen_tools/gen_hpp.cpp

gen_cpp: gen_tools/gen_cpp.cpp
	g++ -o $@ gen_tools/gen_cpp.cpp

all: gen_dsp gen_hpp gen_cpp 
	rm -f auto/*
	mkdir -p auto
	echo 'building auto faust code'
	$(call auto2hpp,0,1,ba.beat,BaBeat,bpm)
	$(call auto2hpp,1,1,ba.bitcrusher,BaBitcrusher,nbits)
	$(call auto2hpp,1,1,ba.midikey2hz,BaMidikey2hz,)
	$(call auto2hpp,0,1,ba.pulse,BaPulse,length)
	$(call auto2hpp,0,1,ba.pulsen,BaPulsen,length period)
	$(call auto2hpp,1,1,de.delay,DeDelay,8192 d)
	$(call auto2hpp,1,1,de.fdelay,DeFdelay,8192 d)
	$(call auto2hpp,1,1,en.are,EnAre,attack release)
	$(call auto2hpp,1,1,en.adsr,EnAdsr,attack decay sustain release)
	$(call auto2hpp,1,1,fi.bandpass,FiBandpass,2 fl fu)
	$(call auto2hpp,1,1,fi.bandpass6e,FiBandpass6e,fc)
	$(call auto2hpp,1,1,fi.highpass,FiHighpass,2 fc)
	$(call auto2hpp,1,1,fi.highpass3e,FiHighpass3e,fc)
	$(call auto2hpp,1,1,fi.highpass6e,FiHighpass6e,fc)
	$(call auto2hpp,1,1,fi.highpassLR4,FiHighpassLR4,cf)
	$(call auto2hpp,1,1,fi.lowpass,FiLowpass,2 fc)
	$(call auto2hpp,1,1,fi.lowpass3e,FiLowpass3e,fc)
	$(call auto2hpp,1,1,fi.lowpass6e,FiLowpass6e,fc)
	$(call auto2hpp,1,1,fi.lowpassLR4,FiLowpassLR4,cf)
	$(call auto2hpp,1,1,fi.resonlp,FiResonlp,fc q gain)
	$(call auto2hpp,1,1,fi.resonhp,FiResonhp,fc q gain)
	$(call auto2hpp,1,1,fi.resonbp,FiResonbp,fc q gain)
	$(call auto2hpp,1,1,fi.zero,FiZero,z)
	$(call auto2hpp,1,1,fi.pole,FiPole,p)
	$(call auto2hpp,1,1,fi.dcblockerat,FiDcblockerat,fb)
	$(call auto2hpp,0,1,os.osc,OsOsc,freq)
	$(call auto2hpp,1,1,os.osc,OsOscF,)
	$(call auto2hpp,0,1,os.sawtooth,OsSawtooth,freq)
	$(call auto2hpp,1,1,os.sawtooth,OsSawtoothF)
	$(call auto2hpp,0,1,os.triangle,OsTriangle,freq)
	$(call auto2hpp,0,1,os.triangle,OsTriangleF,)
	$(call auto2hpp,0,1,os.square,OsSquare,freq)
	$(call auto2hpp,0,1,os.square,OsSquareF,)
	$(call auto2hpp,0,1,no.noise,NoNoise,)
	$(call auto2hpp,1,1,re.mono_freeverb,ReMonoFreeverb,fb1 fb2 damp spread)
	echo 'building user faust code'
	$(call dsp2hpp,1,1,biscale,ZzBiscale,low up)
	$(call dsp2hpp,1,1,comb,ZzComb,rtime coef_y coef_x)
	$(call dsp2hpp,1,1,tenv,ZzTenv,atk hold rel)
	$(call dsp2hpp,1,1,tenvx,ZzTenvx,atk hold rel)
	$(call dsp2hpp,0,1,fm,ZzFm,carry modulator index)
	$(call dsp2hpp,0,1,metro,ZzMetro,bpm)
	$(call dsp2hpp,1,1,port,ZzPort,cx)
	$(call dsp2hpp,2,1,tport,ZzTport,cx)
	$(call dsp2hpp,3,1,select,ZzSelect,)
	$(call dsp2hpp,3,1,switch,ZzSwitch,)
	$(call dsp2hpp,0,1,tick,ZzTick,)
	$(call dsp2hpp,1,1,vibrato,ZzVibrato,freq phase attack release)

clean:
	rm -f gen_dsp gen_hpp gen_cpp 


