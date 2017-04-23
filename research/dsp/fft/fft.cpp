
#include "FourierTransform.h"
#include <iomanip>


int main(int argc, const char* argv[])
{
    cout << fixed << setprecision(3);

    string mode = "spectrum";

    int sampleRate = 48000;
    int windowSize = 0;


    if (argc > 2)
    {
        mode = argv[1];
        windowSize = atoi(argv[2]);
    }
    else
    {
        cout << "ERROR: Not enough arguments specified...\
        \nUsage: FFT_Test <mode> <window_size>\n";
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


    FourierTransform ft(windowSize);


    if (mode == "spectrum")
    {
        // Compute and print the spectrum
        //ft.slowDFT(signal, spectrum);
        //ft.simpleDFT(signal, spectrum);
        //ft.optimizedDFT(signal, spectrum);
        //ft.recursiveFFT(signal, spectrum);
        ft.FFT(signal, spectrum);

        for (int k = 0; k < windowSize; ++k)
        {
            float frequency = (float)k / windowSize * sampleRate;
            float magnitude = 20.0f * log10f(abs(spectrum[k]));

            cout << frequency << "\t" << magnitude << "\n";
        }
    }
    else if (mode == "timer")
    {
        // Time the different FT's
        chrono::steady_clock::time_point begin, end;

        // Time the slow DFT
        begin = chrono::steady_clock::now();
        ft.slowDFT(signal, spectrum);
        end = chrono::steady_clock::now();
        cout << "     Slow DFT duration in microseconds:\t";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        // Time the simple DFT
        begin = chrono::steady_clock::now();
        ft.simpleDFT(signal, spectrum);
        end = chrono::steady_clock::now();
        cout << "   Simple DFT duration in microseconds:\t";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        // Time the optimized DFT
        begin = chrono::steady_clock::now();
        ft.optimizedDFT(signal, spectrum);
        end = chrono::steady_clock::now();
        cout << "Optimized DFT duration in microseconds:\t";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        // Time the recursive FFT
        begin = chrono::steady_clock::now();
        ft.recursiveFFT(signal, spectrum);
        end = chrono::steady_clock::now();
        cout << "Recursive FFT duration in microseconds:\t";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        // Time the FFT
        begin = chrono::steady_clock::now();
        ft.FFT(signal, spectrum);
        end = chrono::steady_clock::now();
        cout << "          FFT duration in microseconds:\t";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }


    return 0;
}
