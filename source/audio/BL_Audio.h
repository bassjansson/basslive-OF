#pragma once

#include "BL_Core.h"

namespace BassLive
{
    // Audio Sample, was: sample
    struct AudioSample
    {
        AudioSample()            { L = R = 0.0f;  };
        AudioSample(Float value) { L = R = value; };

        Float L, R;
    };


    // Audio Clock
    struct AudioClock
    {
        ULong clock;
    };





    //////////////// OLD ////////////////

    class AudioParameter; // was: AudioInput
    class AudioProcessor; // was: AudioModule
}
