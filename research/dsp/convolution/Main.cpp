
#include "FourierTransform.h"
#include <iomanip>


int main(int argc, const char* argv[])
{
    cout << fixed << setprecision(3);

    string mode = "spectrum";

    sigi sampleRate = 48000;
    sigi N = 4096;


    if (argc > 1)
    {
        mode = argv[1];
    }
    else
    {
        cout << "ERROR: Not enough arguments specified...\
        \nUsage: Convolution <mode>\n";
        return 1;
    }


    sigc* input    = new sigc[N];
    sigc* output   = new sigc[N];
    sigc* spectrum = new sigc[N];


    sigf freq = 300; // Hz
    sigi rhythm = N / 1.4;

    for (sigi n = 0; n < N / 2; ++n)
    {
        input[n] = SIG_TWO * sin(SIG_TWO * M_PI * freq / sampleRate * n) * (n % rhythm) / rhythm;
        //input[n] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }

    rhythm = N / 4.5;

    for (sigi n = N / 2; n < N; ++n)
    {
        input[n] = SIG_TWO * sin(SIG_TWO * M_PI * freq / sampleRate * n) * (n % rhythm) / rhythm;
        //input[n] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }


    FourierTransform ft(N);

    if (mode == "input")
    {
        for (sigi n = 0; n < N; ++n)
            cout << n << "\t" << real(input[n]) << "\n";
    }

    ft.forward(input, spectrum);

    if (mode == "response")
    {
        for (sigi k = 0; k < N; ++k)
        {
            sigf freq = (sigf)k / N * sampleRate;
            sigf magn = 20.0 * log10(abs(spectrum[k]));

            cout << freq << "\t" << magn << "\n";
        }
    }

    ft.logarithm(spectrum);
    ft.forward(spectrum, spectrum);

    if (mode == "t-var")
    {
        for (sigi k = 0; k < N; ++k)
            cout << k << "\t" << abs(spectrum[k]) << "\n";
    }

    ft.backward(spectrum, spectrum);
    ft.exponential(spectrum);
    ft.backward(spectrum, output);

    if (mode == "output")
    {
        for (sigi n = 0; n < N; ++n)
            cout << n << "\t" << real(output[n]) << "\n";
    }




    delete[] input;
    delete[] output;
    delete[] spectrum;


    return 0;
}
