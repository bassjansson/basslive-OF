
#include "FourierTransform.h"
#include <iomanip>


int main(int argc, const char* argv[])
{
    cout << fixed << setprecision(3);

    string mode = "spectrum";

    sigi sampleRate = 48000;
    sigi N = 2048;


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


    sigf* input    = new sigf[N];
    sigf* output   = new sigf[N];
    sigc* spectrum = new sigc[N];


    sigf freq = 300; // Hz

    for (sigi n = 0; n < N; ++n)
    {
        input[n] = sin(SIG_TWO * M_PI * freq / sampleRate * n);
        //input[n] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }


    FourierTransform ft(N);

    ft.forward(input, spectrum);
    ft.backward(spectrum, output);


    if (mode == "input")
    {
        for (int n = 0; n < N; ++n)
            cout << n << "\t" << input[n] << "\n";
    }
    else if (mode == "output")
    {
        for (int n = 0; n < N; ++n)
            cout << n << "\t" << output[n] << "\n";
    }
    else if (mode == "response")
    {
        for (sigi k = 0; k < N; ++k)
        {
            sigf freq = (sigf)k / N * sampleRate;
            sigf magn = 20.0 * log10(abs(spectrum[k]));

            cout << freq << "\t" << magn << "\n";
        }
    }


    delete[] input;
    delete[] output;
    delete[] spectrum;


    return 0;
}
