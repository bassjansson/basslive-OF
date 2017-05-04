
#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include "Defines.h"


class FourierTransform
{
public:
     FourierTransform(sigi size);
    ~FourierTransform();

    void  forward(sigc* input, sigc* output);
    void backward(sigc* input, sigc* output);

    void   logarithm(sigc* input);
    void exponential(sigc* input);

private:
    sigi N, NHalf, Nr, NrHalf;
    sigi n, k, r, repeat;

    sigc XOdd;
    sigc *Z, *X, *Y, *swap;
};


#endif /* FAST_FOURIER_TRANSFORM_H */
