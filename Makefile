.PHONY: all

all: synth mono

_FLAGS = 
_INC = 
_LINK = 
ifeq (,$(shell which llvm-config))
	_LLVM = false
else
	_LLVM = true
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
#### LINUX ###########
ifeq ($(_LLVM),true)
	_FLAGS += -Wno-maybe-uninitialized -Wno-delete-non-virtual-dtor -Wno-array-bounds -fopenmp  -D__LINUX_ALSA__ -D_FAUST_FACTORY_
	_INC += -I. -I./eigen3 -I/home/teaonly/opt/faust/include `llvm-config --cflags`
	_LINK += `llvm-config --ldflags` -L/home/teaonly/opt/faust/lib `llvm-config --libs` -lfaust  \
	         -lasound -lsndfile -lpthread -lm -ldl -lz -ltinfo 
else
	_FLAGS += -Wno-maybe-uninitialized -Wno-delete-non-virtual-dtor -Wno-array-bounds -fopenmp  -D__LINUX_ALSA__
	_INC += -I. -I./eigen3 -I/home/teaonly/opt/faust/include
	_LINK += -lasound -lsndfile -lpthread -lm
endif
#### LINUX END #########
endif


ifeq ($(UNAME_S),Darwin)
#### MacOS ###########
ifeq ($(_LLVM),true)
	_FLAGS += -Wno-delete-non-abstract-non-virtual-dtor -D__MACOSX_CORE__ -D_FAUST_FACTORY_
	_INC += -I. -I./eigen3 -I/opt/homebrew/include -I/Users/teaonly/opt/faust/include  `llvm-config --cflags`
	_LINK += `llvm-config --ldflags`  -L/opt/homebrew/lib -L/Users/teaonly/opt/faust/lib `llvm-config --libs` -lfaust -lfaustwithllvm \
			 -lsndfile -lpthread -lm -framework Corefoundation -framework Coreaudio -framework CoreMIDI
else
	_FLAGS += -Wno-delete-non-abstract-non-virtual-dtor -D__MACOSX_CORE__
	_INC += -I. -I./eigen3 -I/opt/homebrew/include -I/Users/teaonly/opt/faust/include
	_LINK += -L/opt/homebrew/lib -lsndfile -lpthread -lm -framework Corefoundation -framework Coreaudio -framework CoreMIDI
endif
#### MacOS END #########
endif

FLAGS = -std=c++2a -O3 -Wall ${_FLAGS} 
INC = ${_INC}
LINK = ${_LINK}


OBJS_DIR = ./objs

OTHERS_SRCS = lr.cpp \
			  fs/tools.cpp \
			  zz/zz_impl.cpp \
			  io/RtAudio.cpp io/RtMidi.cpp io/io_impl.cpp \
			  nn/wavenet.cpp

ifeq ($(_LLVM),true)
	OTHERS_SRCS += fs/factory.cpp
endif

FAUST_SRCS_ = BaBeat.cpp BaBitcrusher.cpp BaMidikey2hz.cpp BaPulse.cpp BaPulsen.cpp \
			  DeDelay.cpp DeFdelay.cpp \
			  FiBandpass6e.cpp FiHighpass3e.cpp FiHighpass6e.cpp FiHighpassLR4.cpp \
			  FiLowpass3e.cpp FiLowpass6e.cpp FiLowpassLR4.cpp \
			  FiResonlp.cpp FiResonhp.cpp FiResonbp.cpp \
			  FiZero.cpp FiPole.cpp FiDcblockerat.cpp \
			  FiBandpass.cpp FiHighpass.cpp FiLowpass.cpp \
			  OsOsc.cpp OsSawtooth.cpp OsTriangle.cpp OsSquare.cpp \
			  OsOscF.cpp OsSawtoothF.cpp OsTriangleF.cpp OsSquareF.cpp \
			  NoNoise.cpp ReMonoFreeverb.cpp EnAre.cpp EnAdsr.cpp \
			  ZzVibrato.cpp ZzFm.cpp ZzPort.cpp ZzTport.cpp ZzComb.cpp \
			  ZzTenv.cpp ZzTenvx.cpp ZzTick.cpp ZzBiscale.cpp ZzSelect.cpp \
			  ZzSwitch.cpp ZzMetro.cpp
FAUST_SRCS = ${FAUST_SRCS_:%.cpp=fs/auto/%.cpp}

ALL_SRCS = ${OTHERS_SRCS} ${FAUST_SRCS}
ALL_OBJS = ${ALL_SRCS:%.cpp=$(OBJS_DIR)/%.o}

$(OBJS_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	g++ $(FLAGS) $(INC) -c -o $@ $< 

mono: $(ALL_OBJS) mono.cpp
	g++ $(FLAGS) $(INC) -c -o $(OBJS_DIR)/mono.o mono.cpp
	g++ $(FLAGS) -o $@ $(OBJS_DIR)/mono.o $(ALL_OBJS) $(LINK)

synth: $(ALL_OBJS) synth.cpp
	g++ $(FLAGS) $(INC) -c -o $(OBJS_DIR)/synth.o synth.cpp
	g++ $(FLAGS) -o $@ $(OBJS_DIR)/synth.o $(ALL_OBJS) $(LINK)

clean:
	rm -rf $(OBJS_DIR)
	rm -f synth mono
