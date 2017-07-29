#include "BL_Audio_BufferMethods.h"

namespace BassLive
{
    namespace Audio
    {
        void SetAllSamplesToZeroOf(SampleBuffer& buffer)
        {
            UInt size = buffer.size();

            for (UInt i = 0; i < size; ++i)
                buffer[i] = 0.0f;
        }

        void SetupAudioBuffer(AudioBuffer& buffer, UInt numberOfChannels, UInt numberOfSamples)
        {
            buffer.resize(numberOfChannels);

            for (UInt i = 0; i < numberOfChannels; ++i)
            {
                buffer[i].resize(numberOfSamples);
                SetAllSamplesToZeroOf(buffer[i]);
            }
        }

        Sample GetInterpolatedSampleOf(const SampleBuffer& buffer, Float pointer)
        {
            UInt intp = (UInt)pointer;
            Float diff = pointer - intp;

            return (1.0f - diff) * buffer[intp] + diff * buffer[intp + 1];
        }

        Float GetRootMeanSquareOf(const SampleBuffer& buffer)
        {
            UInt size = buffer.size();
            Float RMS = 0.0f;

            for (UInt i = 0; i < size; ++i)
                RMS += buffer[i] * buffer[i];

            return sqrtf(RMS / (Float)size);
        }
    }
}
