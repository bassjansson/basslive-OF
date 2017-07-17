#include "BL_Audio_Buffers.h"

namespace BassLive
{
    namespace Audio
    {
        Sample interpolate(const SampleBuffer& buffer, Sample pointer)
        {
            UInt pL = UInt(pointer.L);
            UInt pR = UInt(pointer.R);

            Float fL = pointer.L - pL;
            Float fR = pointer.R - pR;

            Sample sample;

            sample.L = (1.0f - fL) * buffer[pL].L + fL * buffer[pL + 1].L;
            sample.R = (1.0f - fR) * buffer[pR].R + fR * buffer[pR + 1].R;

            return sample;
        }

        Sample rootMeanSquare(const SampleBuffer& buffer)
        {
            UInt bufferSize = buffer.size();
            Sample RMS = 0.0f;

            for (UInt i = 0; i < bufferSize; ++i)
            {
                RMS.L += buffer[i].L * buffer[i].L;
                RMS.R += buffer[i].R * buffer[i].R;
            }
            
            RMS.L = sqrtf(RMS.L / bufferSize);
            RMS.R = sqrtf(RMS.R / bufferSize);
            
            return RMS;
        }
    }
}
