#pragma once

#include "BL_Core.h"

namespace BassLive
{
    namespace Audio
    {
        // was: sample
        struct Sample
        {
            Sample()            { L = R = 0.0f;  };
            Sample(Float value) { L = R = value; };

            Float L, R;
        };

        struct Clock
        {
            ULong clock;
        };
    }
}
