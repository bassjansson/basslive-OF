
#include "FastFourierTransform.h"


void FastFourierTransform::warning(string message)
{
    cout << "[FFT] WARNING: " << message << endl;
}

FastFourierTransform::FastFourierTransform(SigI windowSize)
{
    N = windowSize;

    if (N & (N - 1))
    {
        warning("The specified window size is not a power of 2.\
        \nSetting window size to zero.");

        N = 0;
    }

    NHalf = N / 2;

    ZBuffer.resize(N);

    for (int k = 0; k < N; ++k)
    {
        SigF theta = SIG_TWO * M_PI * k / N;
        ZBuffer[k] = SigC(cos(theta), sin(theta));
    }
}

FastFourierTransform::~FastFourierTransform()
{
    ZBuffer.clear();
}

// A slow DFT with all calculations in it and no optimizations.
void FastFourierTransform::slowDFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    for (int k = 0; k < N; ++k)
    {
        X[k] = SIG_ZERO;

        for (int n = 0; n < N; ++n)
        {
            SigF theta = SIG_TWO * M_PI * k / N * -n;

            SigC Z = SigC(cos(theta), sin(theta));

            X[k] += x[n] * Z;
        }

        X[k] /= N / 2;
    }
}

// A simple DFT with minimum amount of calculations.
void FastFourierTransform::simpleDFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    for (int k = 0; k < N; ++k)
    {
        X[k] = SIG_ZERO;

        for (int n = 0; n < N; ++n)
            X[k] += x[n] * ZBuffer[(k * (N - n)) % N];

        X[k] /= NHalf;
    }
}
