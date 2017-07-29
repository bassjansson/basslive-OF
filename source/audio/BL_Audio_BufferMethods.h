#pragma once

#include "BL_Audio.h"

namespace BassLive
{
    namespace Audio
    {
        void SetAllSamplesToZeroOf(SampleBuffer& buffer);
        void SetupAudioBuffer(AudioBuffer& buffer, UInt numberOfChannels, UInt numberOfSamples);

        Sample GetInterpolatedSampleOf(const SampleBuffer& buffer, Float pointer);
        Float GetRootMeanSquareOf(const SampleBuffer& buffer);
    }
}
