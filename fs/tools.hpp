#ifndef _FAUST_TOOLS_HPP_
#define _FAUST_TOOLS_HPP_

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <cmath>

namespace lr { namespace fs {
    inline FAUSTFLOAT ba_midikey2hz(unsigned char midi) {
        return FAUSTFLOAT(4.4e+02f * std::pow(2.0f, 0.083333336f * ( (float)midi + -69.0f)));
    }

    float random();
}}



#endif
