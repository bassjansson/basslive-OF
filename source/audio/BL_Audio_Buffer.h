#pragma once

#include "BL_Audio.h"
#include "BL_Core_Buffer.h"

namespace BassLive
{
    class AudioBuffer : Buffer<AudioSample> // was: AudioSignal, sig
    {
    public:
        AudioSample interpolate(AudioSample pointer);
        AudioSample rootMeanSquare();
    };

    typedef AudioBuffer* AudioBufferPtr; // was: used for sig_vec
}
