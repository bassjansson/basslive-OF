#include "BL_Audio_BufferMethods.h"

namespace BassLive
{
    namespace Audio
    {
        void SetAllSamplesToZero(SampleBuffer& buffer)
        {
            for (UInt i = 0; i < buffer.size(); ++i)
                buffer[i] = 0.0f;
        }

        void SetupAudioBuffer(AudioBuffer& buffer, UInt numberOfChannels, UInt numberOfSamples)
        {
            buffer.resize(numberOfChannels);

            for (UInt i = 0; i < buffer.size(); ++i)
            {
                buffer[i].resize(numberOfSamples);
                SetAllSamplesToZero(buffer[i]);
            }
        }

        Sample GetInterpolatedSample(const SampleBuffer& buffer, Float pointer)
        {
            UInt intp = (UInt)pointer;
            Float diff = pointer - intp;

            return (1.0f - diff) * buffer[intp] + diff * buffer[intp + 1];
        }

        Float GetRootMeanSquare(const SampleBuffer& buffer)
        {
            UInt size = buffer.size();
            Float RMS = 0.0f;

            for (UInt i = 0; i < size; ++i)
                RMS += buffer[i] * buffer[i];

            return sqrtf(RMS / (Float)size);
        }
    }
}
