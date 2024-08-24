#include "fs/tools.hpp"
#include "fs/dsp.hpp"
#include "fs/auto/NoNoise~.hpp"

namespace lr { namespace fs {
    float random() {
        static mydsp::NoNoise dsp;

        float dout_;
        float* dout[1];
        dout[0] = &dout_;

        dsp.compute(1, nullptr, dout);

        return dout_;
    }
}}

