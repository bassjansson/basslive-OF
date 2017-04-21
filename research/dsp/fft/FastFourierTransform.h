
#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include "Defines.h"


class FastFourierTransform
{
public:
     FastFourierTransform(SigI size);
    ~FastFourierTransform();

    void slowDFT(SigFVec& input, SigCVec& output);

private:
    void warning(string message);

    SigI N;
    SigCVec ZBuffer;
};


#endif /* FAST_FOURIER_TRANSFORM_H */
