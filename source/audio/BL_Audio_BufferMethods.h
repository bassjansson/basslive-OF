#pragma once

#include "BL_Audio.h"

namespace BassLive
{
    namespace Audio
    {
        void SetAllSamplesToZero(SampleBuffer& buffer);
        void SetupAudioBuffer(AudioBuffer& buffer, UInt numberOfChannels, UInt numberOfSamples);

        Sample GetInterpolatedSample(const SampleBuffer& buffer, Float pointer);
        Float GetRootMeanSquare(const SampleBuffer& buffer);
    }
}
