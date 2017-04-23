
#include "FourierTransform.h"


void FourierTransform::warning(string message)
{
    cout << "[FFT] WARNING: " << message << endl;
}

FourierTransform::FourierTransform(SigI windowSize)
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
    NrHalf = Nr / 2;
    n = k = r = 0;
    repeat = 0;

    xZ = SIG_ZERO;
    ZBuffer.resize(N);
    FFTBuffer.resize(N);

    for (int k = 0; k < N; ++k)
    {
        SigF theta = SIG_TWO * M_PI * k / N;
        ZBuffer[k] = SigC(cos(theta), sin(theta));
        FFTBuffer[k] = SIG_ZERO;
    }
}

FourierTransform::~FourierTransform()
{
    ZBuffer.clear();
}

// A slow DFT with all processing in it and no optimizations.
void FourierTransform::slowDFT(SigFVec& x, SigCVec& X)
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
void FourierTransform::simpleDFT(SigFVec& x, SigCVec& X)
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

// An optimized DFT which discards repeated calculations.
// BUT: This one is only faster than the simple DFT if N >= 1024.
void FourierTransform::optimizedDFT(SigFVec& x, SigCVec& X)
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

        for (r = 0; (repeat <= N) && !((n >> r) & 1); ++r)
            repeat *= 2;

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

void FourierTransform::recursiveFFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    recursiveFFT(x, X, N, 0);

    for (k = 0; k < N; ++k)
        X[k] /= NHalf;
}

void FourierTransform::recursiveFFT(SigFVec& x, SigCVec& X, SigI Nr, SigI n)
{
    if (Nr > 1)
    {
        NrHalf = Nr / 2;
        repeat = N / Nr;

        SigCVec XEven, XOdd;
        XEven.resize(NrHalf);
        XOdd.resize(NrHalf);

        recursiveFFT(x, XEven, NrHalf, n);
        recursiveFFT(x, XOdd , NrHalf, n + repeat);

        for (k = 0; k < NrHalf; ++k)
        {
            SigC ZOdd = ZBuffer[k * repeat] * XOdd[k];

            X[k]          = XEven[k] + ZOdd;
            X[k + NrHalf] = XEven[k] - ZOdd;
        }

        XEven.clear();
        XOdd.clear();
    }
    else
    {
        X[0] = x[n];
    }
}

void FourierTransform::FFT(SigFVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    for (n = 0; n < N; ++n)
        FFTBuffer[n] = x[n];

    FFT(FFTBuffer, X);
}

void FourierTransform::FFT(SigCVec& x, SigCVec& X)
{
    if (x.size() != N ||
        X.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    // Iterate through the recursive levels
    for (Nr = 2; Nr <= N; Nr *= 2)
    {
        NrHalf = Nr / 2;
        repeat = N / Nr;

        // Iterate through the nested transforms
        for (int F = 0; F < N; F += Nr)
        {
            // Iterate through half of the current transform length
            for (int i = 0; i < NrHalf; ++i)
            {
                n = i + F / 2;
                k = i + F;

                SigC ZOdd = ZBuffer[i * repeat] * x[n + NHalf];

                X[k]          = x[n] + ZOdd;
                X[k + NrHalf] = x[n] - ZOdd;
            }
        }

        // Copy X back to x
        // TODO: this should be swapping pointers
        for (n = 0; n < N; ++n)
            x[n] = X[n];
    }

    // Perform the N / 2 division on X
    for (k = 0; k < N; ++k)
        X[k] /= NHalf;
}
