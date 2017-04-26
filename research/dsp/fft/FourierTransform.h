
#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include "Defines.h"


class FourierTransform
{
public:
     FourierTransform(SigI size);
    ~FourierTransform();

    void      slowDFT(SigFVec& input, SigCVec& output);
    void    simpleDFT(SigFVec& input, SigCVec& output);
    void optimizedDFT(SigFVec& input, SigCVec& output);

    void recursiveFFT(SigFVec& input, SigCVec& output);
    void          FFT(SigFVec& input, SigCVec& output);

private:
    void recursiveFFT(SigFVec&, SigCVec&, SigI, SigI);
    void warning(string message);

    SigI N, NHalf;
    SigI Nr, NrHalf;
    SigI n, k, r, i;
    SigI repeat;

    SigC xZ, ZOdd;
    SigCVec ZBuffer;

    SigC *x, *X, *swap;
};


#endif /* FAST_FOURIER_TRANSFORM_H */
