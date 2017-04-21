
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

private:
    void warning(string message);

    SigI N, NHalf, Nr;
    SigI n, k, r;
    SigI repeat;

    SigC xZ;
    SigCVec ZBuffer;
};


#endif /* FAST_FOURIER_TRANSFORM_H */
