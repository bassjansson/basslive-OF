
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
    Nr = N;
    n = k = r = 0;
    repeat = 0;

    xZ = SIG_ZERO;
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

// A slow DFT with all processing in it and no optimizations.
void FastFourierTransform::slowDFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    for (SigI k = 0; k < N; ++k)
    {
        X[k] = SIG_ZERO;

        for (SigI n = 0; n < N; ++n)
        {
            SigF theta = SIG_TWO * M_PI * k / N * -n;

            SigC Z = SigC(cos(theta), sin(theta));

            X[k] += x[n] * Z;
        }

        X[k] /= N / 2;
    }
}

// A simple DFT using memory for minimum amount of processing.
void FastFourierTransform::simpleDFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    for (k = 0; k < N; ++k)
    {
        X[k] = SIG_ZERO;

        for (n = 0; n < N; ++n)
            X[k] += x[n] * ZBuffer[(k * (N - n)) % N];

        X[k] /= NHalf;
    }
}

// An optimized DFT discarding repeated calculations.
void FastFourierTransform::optimizedDFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");


    // Clear X first
    for (k = 0; k < N; ++k)
        X[k] = SIG_ZERO;


    // Iterate n first instead of k
    for (n = 0; n < N; ++n)
    {
        // Get the possible amount of repeated calculations
        repeat = 1;

        // TODO: This could be a calculation instead of a for-loop
        // Tip: look at the bit value of n, there you can find the matching r
        for (r = 2; r <= N; r *= 2)
        {
            if (n % r) break;

            repeat = r;
        }

        Nr = N / repeat;

        // Iterate k from 0 to N / repeat
        for (k = 0; k < Nr; ++k)
        {
            xZ = x[n] * ZBuffer[(k * (N - n)) % N];

            for (r = 0; r < repeat; ++r)
                X[k + r * Nr] += xZ;
        }
    }


    // Perform the N / 2 division on X
    for (k = 0; k < N; ++k)
        X[k] /= NHalf;
}
