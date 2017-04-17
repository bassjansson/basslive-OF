
#include <iostream>
#include <cmath>
#include "Filter.h"

using namespace std;


int main (int argc, const char* argv[])
{
    int sampleRate = 48000;

	Filter filter(sampleRate);

    ComplexVector signalIn;
    ComplexVector signalOut;
    ComplexVector response;

    // responseSize is better to be a multiplication of
    // signalSize (for the response resolution)
    // but responseSize >= signalSize is definitely
    // required (for the signal resolution)
    int signalSize = 512;
    int responseSize = 2048;

    signalIn.resize(signalSize);
    signalOut.resize(signalSize);
    response.resize(responseSize);

    float freq = 1000.0f; // Hz
    float phase = 0.0f;

    for (int i = 0; i < signalSize; ++i)
    {
        signalIn[i] = newComplex(sinf(phase), 0);
        phase += freq / sampleRate * 2*M_PI;
    }

    filter.fourierTransform(signalIn, response);
    filter.inverseFourierTransform(response, signalOut);

    if (argc > 1)
    {
        string arg = argv[1];

        if (arg == "input")
        {
            for (int i = 0; i < signalSize; ++i)
                cout << i << "\t" << signalIn[i].real << "\n";
        }
        else if (arg == "output")
        {
            for (int i = 0; i < signalSize; ++i)
                cout << i << "\t" << signalOut[i].real << "\n";
        }
        else if (arg == "response")
        {
            for (int i = 0; i < responseSize; ++i)
            {
                float freq = (float)i / responseSize * sampleRate;
                cout << freq << "\t" << 20.0f * log10f(response[i].real / responseSize * 2) << "\n";
            }
        }
    }

    /* // Test of designing a filter
    filter.addZero(3000,  1);
    filter.addZero(6000,  1);
    filter.addZero(12000, 0.3);
    filter.addZero(24000, 0.15);

    filter.addPole(0,    0.72);
    filter.addPole(4500, 0.93);

    int window = 1024;
    float* response;

    if (argc < 2)
        response = filter.getFrequencyResponse(window);
    else
        response = filter.testFrequencyResponse(window);

    for (int i = 0; i < window; i++)
    {
        float frequency = (float)i / window * sampleRate / 2;
        cout << frequency << "\t" << response[i] << "\n";
    }
    */

    /* // Outputs coefficients
    cout << "\n";

    float* zeros = filter.getZeroCoefficients();

    for (int i = 0; i < filter.getZeroSize(); i++)
    {
        clog << i << ":\t" << zeros[i] << "\n";
    }

    clog << endl;

    float* poles = filter.getPoleCoefficients();

    for (int i = 0; i < filter.getPoleSize(); i++)
    {
        clog << i << ":\t" << poles[i] << "\n";
    }
     */
}
