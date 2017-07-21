#pragma once

#include "BL_Core_Buffer.h"

namespace BassLive
{
    namespace Audio
    {
        typedef Float Sample;
        typedef ULong Clock;

        typedef Buffer<Sample> SampleBuffer;
        typedef Buffer<SampleBuffer> AudioBuffer;
    }
}
