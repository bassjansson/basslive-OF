#include "BL_Audio_Buffer.h"

namespace BassLive
{
    AudioSample AudioBuffer::interpolate(AudioSample pointer)
    {
        UInt pL = UInt(pointer.L);
        UInt pR = UInt(pointer.R);

        Float fL = pointer.L - pL;
        Float fR = pointer.R - pR;

        AudioBuffer& buffer = *this;
        AudioSample sample;

        sample.L = (1.0f - fL) * buffer[pL].L + fL * buffer[pL + 1].L;
        sample.R = (1.0f - fR) * buffer[pR].R + fR * buffer[pR + 1].R;

        return sample;
    }

    AudioSample AudioBuffer::rootMeanSquare()
    {
        AudioBuffer& buffer = *this;
        AudioSample RMS = 0.0f;

        for (UInt i = 0; i < size(); ++i)
        {
            RMS.L += buffer[i].L * buffer[i].L;
            RMS.R += buffer[i].R * buffer[i].R;
        }

        RMS.L = sqrtf(RMS.L / size());
        RMS.R = sqrtf(RMS.R / size());

        return RMS;
    }
}
