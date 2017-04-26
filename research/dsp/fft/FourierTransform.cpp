
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
    n = k = r = i = 0;
    repeat = 0;

    xZ = ZOdd = SIG_ZERO;
    ZBuffer.resize(N);

    x = new SigC[N];
    X = new SigC[N];
    swap = NULL;


    for (int k = 0; k < N; ++k)
    {
        SigF theta = SIG_TWO * M_PI * k / N;
        ZBuffer[k] = SigC(cos(theta), sin(theta));

        x[k] = X[k] = SIG_ZERO;
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
        SigI NrHalf = Nr / 2;
        SigI repeat = N / Nr;

        SigCVec XEven, XOdd;
        XEven.resize(NrHalf);
        XOdd.resize(NrHalf);

        recursiveFFT(x, XEven, NrHalf, n);
        recursiveFFT(x, XOdd , NrHalf, n + repeat);

        for (k = 0; k < NrHalf; ++k)
        {
            ZOdd = ZBuffer[k * repeat] * XOdd[k];

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

void FourierTransform::FFT(SigFVec& input, SigCVec& output)
{
    // Check sizes
    if (input.size() != N ||
        output.size() != N)
        return warning("The specified vectors do not have the required window size.\
        \nAborting transform.");

    // Copy input to x
    // (this is equivelant to the loop below with Nr = 2)
    for (n = 0; n < NHalf; ++n)
    {
        k = n * 2;
        r = n + NHalf;

        x[k]     = input[n] + input[r];
        x[k + 1] = input[n] - input[r];
    }

    // Iterate through the recursive levels
    for (Nr = 4; Nr < N; Nr *= 2)
    {
        NrHalf = Nr / 2;
        repeat = N / Nr;

        for (n = 0; n < NHalf; ++n)
        {
            r = n % NrHalf; // x of matrix
            i = n / NrHalf; // y of matrix
            k = r + i * Nr;

            ZOdd = ZBuffer[r * repeat] * x[n + NHalf];

            X[k]          = x[n] + ZOdd;
            X[k + NrHalf] = x[n] - ZOdd;
        }

        // Swap x and X
        swap = x;
        x = X;
        X = swap;
    }

    // Copy x to output with the N / 2 division
    // (this is equivelant to the loop above with Nr = N)
    SigF NHalfF = NHalf;
    for (n = 0; n < NHalf; ++n)
    {
        ZOdd = ZBuffer[n] * x[n + NHalf];

        output[n]         = (x[n] + ZOdd) / NHalfF;
        output[n + NHalf] = (x[n] - ZOdd) / NHalfF;
    }
}
