
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


    sigc* input    = new sigc[N];
    sigc* mask     = new sigc[N];
    sigc* output   = new sigc[N];
    sigc* spectrum = new sigc[N];


    sigf modFreq = 100; // Hz

    sigf carFreqOffset = 300;
    sigf carFreqDepth = 150;
    sigf carPhase = 0;

    for (sigi n = 0; n < N; ++n)
    {
        float carFreq = carFreqOffset + carFreqDepth * cos(SIG_TWO * M_PI * modFreq / sampleRate * n);
        carPhase += SIG_TWO * M_PI * carFreq / sampleRate;

        float AM = sin(SIG_TWO * M_PI * modFreq / sampleRate * n) * 0.48f + 0.52f;

        input[n] = sigc(cos(carPhase), sin(carPhase)) * AM;
        //input[n] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }

    for (sigi n = 0; n < N; ++n)
    {
        // TODO: it still goes wrong here, creating an imaginary part is hard
        //input[n] = sigc(real(input[n]), real(input[n] - input[(n + 1) % N]) * exp(M_PI));
    }


    if (mode == "inputRe")
    {
        for (sigi n = 0; n < N; ++n)
            cout << n << "\t" << real(input[n]) << "\n";
    }

    if (mode == "inputIm")
    {
        for (sigi n = 0; n < N; ++n)
            cout << n << "\t" << imag(input[n]) << "\n";
    }

    // AM/FM Demodulator
    for (sigi n = 0; n < N; ++n)
    {
        float ampExp = exp(real(log(input[n])));
        float freqDiff = imag(log(input[(n + 1) % N] / input[n]));

        if (freqDiff < 0)
            freqDiff += SIG_TWO * M_PI;

        output[n] = sigc(ampExp, freqDiff);
    }


    if (mode == "ampMod")
    {
        for (sigi n = 0; n < N; ++n)
            cout << n << "\t" << real(output[n]) << "\n";
    }

    if (mode == "freqMod")
    {
        for (sigi n = 0; n < N; ++n)
        {
            cout << n << "\t" << imag(output[n]) / (SIG_TWO * M_PI) * sampleRate / carFreqOffset;
            cout << "\n";
        }
    }

    /*
    FourierTransform ft(N);

    ft.forward(input, spectrum);
    ft.forward(mask, output);

    for (sigi k = 0; k < N; ++k)
        spectrum[k] /= output[k] * (sigf)N;

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
    */



    delete[] input;
    delete[] mask;
    delete[] output;
    delete[] spectrum;


    return 0;
}
