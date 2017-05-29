
#include "FourierTransform.h"
#include <iomanip>


void addWindow(sigc* input, sigi N, bool inverse = false)
{
    for (int n = 0; n < N; ++n)
    {
        // Hamming window
        //float alpha = 0.53836f;
        //float hamming = alpha - (SIG_ONE - alpha) * cos((SIG_TWO * M_PI * n) / (N - 1));

        // Nuttall window
        // float gamma = (M_PI * n) / (N - 1);
        // float nuttall = 0.5f -
        // 0.487396f * cos(2.0f * gamma) +
        // 0.144232f * cos(4.0f * gamma) -
        // 0.012604f * cos(6.0f * gamma);

        // Gaussian window
        float beta = 0.4f; // <= 0.5
        float gaussian = exp(-pow((n - (N - 1) / SIG_TWO) / (beta * (N - 1) / SIG_TWO), SIG_TWO) / SIG_TWO);

        if (inverse) input[n] /= gaussian;
        else         input[n] *= gaussian;
    }
}


int main(int argc, const char* argv[])
{
    //cout << fixed << setprecision(3);

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


    FourierTransform ft(N);


    sigc* input    = new sigc[N];
    sigc* mask     = new sigc[N];
    sigc* output   = new sigc[N];
    sigc* spectrum = new sigc[N];


    sigf modFreq = 100; // Hz

    sigf carFreqOffset = 300;
    sigf carFreqDepth = 75;
    sigf carPhase = 0;

    sigf AMDepth = 0.25f;

    for (sigi n = 0; n < N; ++n)
    {
        sigf carFreq = carFreqOffset + carFreqDepth * cos(SIG_TWO * M_PI * modFreq / sampleRate * n);
        carPhase += SIG_TWO * M_PI * carFreq / sampleRate;

        sigf AM = sin(SIG_TWO * M_PI * modFreq / sampleRate * n) * AMDepth + (SIG_ONE - AMDepth);

        input[n] = sigc(cos(carPhase) * AM, SIG_ZERO);// sin(carPhase) * AM);

        //input[n] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }


    // Add imaginary part
    addWindow(input, N);
    ft.forward(input, spectrum);

    for (int k = 0; k < N / 2; ++k)
        spectrum[k] *= SIG_TWO;

    for (int k = N / 2; k < N; ++k)
        spectrum[k] = SIG_ZERO;

    ft.backward(spectrum, input);
    addWindow(input, N, true);


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

        mask[n] = sigc(ampExp, freqDiff);
    }

    if (mode == "ampMod")
    {
        for (sigi n = 0; n < N; ++n)
            cout << n << "\t" << real(mask[n]) << "\n";
    }

    if (mode == "freqMod")
    {
        for (sigi n = 0; n < N; ++n)
        {
            cout << n << "\t" << imag(mask[n]) / (SIG_TWO * M_PI) * sampleRate / carFreqOffset;
            cout << "\n";
        }
    }

    /*
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
