
#include "FastFourierTransform.h"
#include <iomanip>


int main(int argc, const char* argv[])
{
    int sampleRate = 48000;
    int windowSize = 0;
    cout << fixed << setprecision(3);

    if (argc > 1)
    {
        windowSize = atoi(argv[1]);
    }
    else
    {
        cout << "No window size specified, returning error 1.\n";
        return 1;
    }

    SigFVec signal;
    SigCVec spectrum;

    signal.resize(windowSize);
    spectrum.resize(windowSize);

    float freq = 1000.0f; // Hz

    for (int n = 0; n < windowSize; ++n)
        signal[n] = sinf(2.0f * M_PI * freq / sampleRate * n);

    // for (int n = 0; n < windowSize; ++n)
    //     signal[n] = (float)rand() / RAND_MAX * 2.0f - 1.0f;


    chrono::steady_clock::time_point begin, end;

    FastFourierTransform fft(windowSize);

    // Time the slow DFT
    begin = chrono::steady_clock::now();
    fft.slowDFT(signal, spectrum);
    end = chrono::steady_clock::now();
    cout << "  Slow DFT duration in microseconds:\t";
    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

    // Time the simple DFT
    begin = chrono::steady_clock::now();
    fft.simpleDFT(signal, spectrum);
    end = chrono::steady_clock::now();
    cout << "Simple DFT duration in microseconds:\t";
    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;


    // Print the spectrum
    // for (int k = 0; k < windowSize; ++k)
    // {
    //     float frequency = (float)k / windowSize * sampleRate;
    //     float magnitude = 20.0f * log10f(abs(spectrum[k]));
    //
    //     cout << frequency << "\t";
    //     cout << magnitude << "\n";
    // }


    // int N = windowSize;
    //
    // for (int n = 0; n < N; ++n)
    // {
    //     cout << "n = " << n << "\n";
    //
    //     // Get the possible amount of repeat
    //     int repeat = 1;
    //
    //     for (int i = 2; i <= N; i *= 2)
    //     {
    //         if (n % i) break;
    //
    //         repeat = i;
    //     }
    //
    //     // Iterate k from 0 to N / repeat
    //     int N_repeat = N / repeat;
    //
    //     for (int k = 0; k < N_repeat; ++k)
    //     {
    //         // With this Z we look up values in the Z buffer
    //         int Z = (n * k) % N;
    //
    //         // The actual product x[n] * Z^-n
    //         //sigc product = signal[n] * Zbuffer[Z];
    //
    //         cout << "\tk = ";
    //
    //         for (int r = 0; r < repeat; ++r)
    //         {
    //             int k_repeat = k + r * N_repeat;
    //
    //             // The actual addition of X[k] = SUM(x[n] * Z^-n)
    //             //spectrum[k_repeat] += product;
    //
    //             cout << k_repeat << ", ";
    //         }
    //
    //         cout << "->\tZ = " << Z << "\n";
    //     }
    //
    //     cout << "\n";
    // }

    return 0;
}
