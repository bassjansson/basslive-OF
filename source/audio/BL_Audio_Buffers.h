#pragma once

#include "BL_Core_Buffer.h"
#include "BL_Audio_Data.h"

namespace BassLive
{
    namespace Audio
    {
        // was: AudioSignal, sig
        typedef Buffer<Sample> SampleBuffer;

        Sample interpolate(const SampleBuffer& buffer, Sample pointer);

        Sample rootMeanSquare(const SampleBuffer& buffer);
    }
}
