
#include "FourierTransform.h"


void warning(string message)
{
    cout << "[FourierTransform] WARNING: " << message << endl;
}

FourierTransform::FourierTransform(sigi size)
{
    N = size;

    if (N & (N - 1))
    {
        warning("The specified window size is not a power of 2.\
        \nSetting window size to zero.");

        N = 0;
    }

    NHalf = N / 2;
    Nr = NrHalf = 0;
    n = k = r = repeat = 0;

    XOdd = SIG_ZERO;

    Z = new sigc[N + 1];
    X = new sigc[N];
    Y = new sigc[N];
    swap = NULL;

    for (k = 0; k < N + 1; ++k)
    {
        sigf theta = -SIG_TWO * M_PI * k / N;
        Z[k] = sigc(cos(theta), sin(theta));
    }

    for (k = 0; k < N; ++k)
        X[k] = Y[k] = SIG_ZERO;
}

FourierTransform::~FourierTransform()
{
    delete[] Z;
    delete[] X;
    delete[] Y;
}

void FourierTransform::forward(sigc* input, sigc* output)
{
    // Copy input to X
    // (this is a faster equivelant to the loop below with Nr = 2)
    for (n = 0; n < NHalf; ++n)
    {
        k = n * 2;
        r = n + NHalf;

        X[k]     = input[n] + input[r];
        X[k + 1] = input[n] - input[r];
    }

    // Iterate through the recursive levels
    for (Nr = 4; Nr < N; Nr *= 2)
    {
        NrHalf = Nr / 2;
        repeat = N / Nr;

        for (n = 0; n < NHalf; ++n)
        {
            r = n % NrHalf;
            k = r + (n / NrHalf) * Nr;

            XOdd = Z[r * repeat] * X[n + NHalf];

            Y[k]          = X[n] + XOdd;
            Y[k + NrHalf] = X[n] - XOdd;
        }

        // Swap X and Y
        swap = X;
        X = Y;
        Y = swap;
    }

    // Copy X / N to output
    // (this is a faster equivelant to the loop above with Nr = N)
    for (n = 0; n < NHalf; ++n)
    {
        XOdd = Z[n] * X[n + NHalf];

        output[n]         = (X[n] + XOdd) / (sigf)N;
        output[n + NHalf] = (X[n] - XOdd) / (sigf)N;
    }
}

void FourierTransform::backward(sigc* input, sigc* output)
{
    // Copy input to X
    // (this is a faster equivelant to the loop below with Nr = 2)
    for (n = 0; n < NHalf; ++n)
    {
        k = n * 2;
        r = n + NHalf;

        X[k]     = input[n] + input[r];
        X[k + 1] = input[n] - input[r];
    }

    // Iterate through the recursive levels
    for (Nr = 4; Nr < N; Nr *= 2)
    {
        NrHalf = Nr / 2;
        repeat = N / Nr;

        for (n = 0; n < NHalf; ++n)
        {
            r = n % NrHalf;
            k = r + (n / NrHalf) * Nr;

            XOdd = Z[N - r * repeat] * X[n + NHalf];

            Y[k]          = X[n] + XOdd;
            Y[k + NrHalf] = X[n] - XOdd;
        }

        // Swap X and Y
        swap = X;
        X = Y;
        Y = swap;
    }

    // Copy real(X) to output
    // (this is a faster equivelant to the loop above with Nr = N)
    for (n = 0; n < NHalf; ++n)
    {
        XOdd = Z[N - n] * X[n + NHalf];

        output[n]         = X[n] + XOdd;
        output[n + NHalf] = X[n] - XOdd;
    }
}

void FourierTransform::logarithm(sigc* input)
{
    for (n = 0; n < N; ++n)
        input[n] = log(input[n]);
}

void FourierTransform::exponential(sigc* input)
{
    for (n = 0; n < N; ++n)
        input[n] = exp(input[n]);
}
