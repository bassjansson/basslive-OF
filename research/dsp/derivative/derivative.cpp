#include <iostream>
#include <cmath>

using namespace std;


void normalize(double* input, int size) // Destructive
{
    if (size < 1) return;


    // Get most and least value in input
    double most = 0.0;
    double least = 0.0;

    for (int i = 0; i < size; ++i)
    {
        double in = input[i];

        if (in > most)  most  = in;
        if (in < least) least = in;
    }


    // Get offset and gain (substracter & product)
    double offset = (most + least) * 0.5;
    double gain;

    if (offset != most)
        gain = 1.0 / (most - offset);
    else
        gain = 0.0; // This is a guess


    // Apply offset and gain to input
    for (int i = 0; i < size; ++i)
        input[i] = (input[i] - offset) * gain;
}

void derivative(double*& input, int& size) // Destructive
{
    if (size < 2) return;

    size -= 1;
    double* output = new double[size];

    for (int i = 0; i < size; ++i)
        output[i] = input[i + 1] - input[i];

    delete[] input;

    input = output;
}

void onepole(double*& input, int& size, double factor)
{
    if (size < 2) return;

    if (factor > 1.0) factor = 1.0;
    if (factor < 0.0) factor = 0.0;

    size -= 1;
    double* output = new double[size];

    for (int i = 0; i < size; ++i)
        output[i] = factor * input[i] + (1.0 - factor) * input[i + 1];

    delete[] input;

    input = output;
}

void bitcrush(double* input, int size, int bits)
{
    if (size < 1) return;

    if (bits < 1) bits = 1;

    double max = pow(2.0, bits - 1);

    for (int i = 0; i < size; ++i)
        input[i] = int(input[i] * max + 0.5) / max;
}

int main(int argc, const char* argv[])
{
    // Setup
    double sampleRate = 12000.0;  // Hertz
    double signalDuration = 50.0; // Milliseconds

    int signalSize = int(0.001 * signalDuration * sampleRate);
    double* signal = new double[signalSize];

    double phase1 = 1.0;   // Radians
    double phase2 = 0.777; // Radians

    double freq1 = 250.0; // Hertz
    double freq2 = 111.0; // Hertz


    // Fill the signal with the two sines
    for (int i = 0; i < signalSize; ++i)
    {
        signal[i] = (sinf(phase1) + sinf(phase2));

        phase1 += freq1 / sampleRate * 2*M_PI;
        phase2 += freq2 / sampleRate * 2*M_PI;
    }

    // Normalize the signal
    normalize(signal, signalSize);


    // Process command line arguments
    int N = 0; // number of processes
    double f = 0.0; // one pole filter coefficient
    int b = 16; // bit depth of the signal

    if (argc > 1) N = stoi(argv[1]);
    if (argc > 2) b = stoi(argv[2]);
    if (argc > 3) f = stod(argv[3]);


    // Process the signal N times
    for (int i = 0; i < N; ++i)
    {
        derivative(signal, signalSize);
        normalize(signal, signalSize);
        onepole(signal, signalSize, f);
        bitcrush(signal, signalSize, b);
        normalize(signal, signalSize);
    }


    // Output the signal
    for (int i = 0; i < signalSize; ++i)
    {
        float ms = 1000.0 * i / sampleRate;
        cout << ms << "\t" << signal[i] << "\n";
    }
}
