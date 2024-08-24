#ifndef _FAUST_IMPL_HPP_
#define _FAUST_IMPL_HPP_

#include "lr.hpp"
#include "fs/auto/BaBeat.hpp"
#include "fs/auto/BaBitcrusher.hpp"
#include "fs/auto/BaMidikey2hz.hpp"
#include "fs/auto/BaPulse.hpp"
#include "fs/auto/BaPulsen.hpp"
#include "fs/auto/DeDelay.hpp"
#include "fs/auto/DeFdelay.hpp"
#include "fs/auto/EnAre.hpp"
#include "fs/auto/EnAdsr.hpp"
#include "fs/auto/FiBandpass.hpp"
#include "fs/auto/FiBandpass6e.hpp"
#include "fs/auto/FiHighpass.hpp"
#include "fs/auto/FiHighpass3e.hpp"
#include "fs/auto/FiHighpass6e.hpp"
#include "fs/auto/FiHighpassLR4.hpp"
#include "fs/auto/FiLowpass.hpp"
#include "fs/auto/FiLowpass3e.hpp"
#include "fs/auto/FiLowpass6e.hpp"
#include "fs/auto/FiLowpassLR4.hpp"
#include "fs/auto/FiResonlp.hpp"
#include "fs/auto/FiResonhp.hpp"
#include "fs/auto/FiResonbp.hpp"
#include "fs/auto/FiZero.hpp"
#include "fs/auto/FiPole.hpp"
#include "fs/auto/FiDcblockerat.hpp"
#include "fs/auto/OsOsc.hpp"
#include "fs/auto/OsOscF.hpp"
#include "fs/auto/OsSawtooth.hpp"
#include "fs/auto/OsSawtoothF.hpp"
#include "fs/auto/OsSquare.hpp"
#include "fs/auto/OsSquareF.hpp"
#include "fs/auto/OsTriangle.hpp"
#include "fs/auto/OsTriangleF.hpp"
#include "fs/auto/NoNoise.hpp"
#include "fs/auto/ReMonoFreeverb.hpp"

#include "fs/auto/ZzVibrato.hpp"
#include "fs/auto/ZzPort.hpp"
#include "fs/auto/ZzTport.hpp"
#include "fs/auto/ZzFm.hpp"
#include "fs/auto/ZzComb.hpp"
#include "fs/auto/ZzTenv.hpp"
#include "fs/auto/ZzTenvx.hpp"
#include "fs/auto/ZzTick.hpp"
#include "fs/auto/ZzBiscale.hpp"
#include "fs/auto/ZzSelect.hpp"
#include "fs/auto/ZzSwitch.hpp"
#include "fs/auto/ZzMetro.hpp"

#ifdef _FAUST_FACTORY_
#include "fs/factory.hpp"
#endif

namespace lr { namespace fs {

void init_words(Enviroment& env) {
    env.insert_native_word("fs.ba.beat", BaBeatWord::creator);
    env.insert_native_word("fs.ba.bitcrusher", BaBitcrusherWord::creator);
    env.insert_native_word("fs.ba.midikey2hz", BaMidikey2hzWord::creator);
    env.insert_native_word("fs.ba.pulse", BaPulseWord::creator);
    env.insert_native_word("fs.ba.pulsen", BaPulsenWord::creator);

    env.insert_native_word("fs.de.delay", DeDelayWord::creator);
    env.insert_native_word("fs.de.fdelay", DeFdelayWord::creator);

    env.insert_native_word("fs.en.are", EnAreWord::creator);
    env.insert_native_word("fs.en.adsr", EnAdsrWord::creator);

    env.insert_native_word("fs.fi.lowpass", FiLowpassWord::creator);
    env.insert_native_word("fs.fi.highpass", FiHighpassWord::creator);
    env.insert_native_word("fs.fi.bandpass", FiBandpassWord::creator);
    env.insert_native_word("fs.fi.bandpass6e", FiBandpass6eWord::creator);
    env.insert_native_word("fs.fi.highpass3e", FiHighpass3eWord::creator);
    env.insert_native_word("fs.fi.highpass6e", FiHighpass6eWord::creator);
    env.insert_native_word("fs.fi.highpassLR4", FiHighpassLR4Word::creator);
    env.insert_native_word("fs.fi.lowpass3e", FiHighpass3eWord::creator);
    env.insert_native_word("fs.fi.lowpass6e", FiHighpass6eWord::creator);
    env.insert_native_word("fs.fi.lowpassLR4", FiLowpass3eWord::creator);

    env.insert_native_word("fs.fi.resonlp", FiResonlpWord::creator);
    env.insert_native_word("fs.fi.resonhp", FiResonhpWord::creator);
    env.insert_native_word("fs.fi.resonbp", FiResonbpWord::creator);

    env.insert_native_word("fs.fi.zero", FiZeroWord::creator);
    env.insert_native_word("fs.fi.pole", FiPoleWord::creator);
    env.insert_native_word("fs.fi.dcblockerat", FiDcblockeratWord::creator);

    env.insert_native_word("fs.no.noise", NoNoiseWord::creator);
    env.insert_native_word("fs.os.osc", OsOscWord::creator);
    env.insert_native_word("fs.os.sawtooth", OsSawtoothWord::creator);
    env.insert_native_word("fs.os.square", OsSquareWord::creator);
    env.insert_native_word("fs.os.triangle", OsTriangleWord::creator);
    env.insert_native_word("fs.os.osc_", OsOscFWord::creator);
    env.insert_native_word("fs.os.sawtooth_", OsSawtoothFWord::creator);
    env.insert_native_word("fs.os.square_", OsSquareFWord::creator);
    env.insert_native_word("fs.os.triangle_", OsTriangleFWord::creator);

    env.insert_native_word("fs.re.mono_freeverb", ReMonoFreeverbWord::creator);

    env.insert_native_word("fs.zz.biscale", ZzBiscaleWord::creator);
    env.insert_native_word("fs.zz.comb", ZzCombWord::creator);
    env.insert_native_word("fs.zz.tenv", ZzTenvWord::creator);
    env.insert_native_word("fs.zz.tenvx", ZzTenvxWord::creator);
    env.insert_native_word("fs.zz.fm", ZzFmWord::creator);
    env.insert_native_word("fs.zz.metro", ZzMetroWord::creator);
    env.insert_native_word("fs.zz.port", ZzPortWord::creator);
    env.insert_native_word("fs.zz.tport", ZzTportWord::creator);
    env.insert_native_word("fs.zz.select", ZzSelectWord::creator);
    env.insert_native_word("fs.zz.switch", ZzSelectWord::creator);
    env.insert_native_word("fs.zz.tick", ZzTickWord::creator);
    env.insert_native_word("fs.zz.vibrato", ZzVibratoWord::creator);

#ifdef _FAUST_FACTORY_
    env.insert_native_word("fs.factory", FaustFactoryWord::creator);
#endif

}

}}


#endif
