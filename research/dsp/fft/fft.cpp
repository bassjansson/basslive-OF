
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>

using namespace std;

// Signal value constants
#define SIG_ZERO 0.0f
#define SIG_ONE  1.0f

// Signal value types
typedef float         sigf;
typedef complex<sigf> sigc;

// Signal vector types
typedef vector<sigf> sigf_vec;
typedef vector<sigc> sigc_vec;

//   signal[n] = x[n]
// response[k] = X[k]
void dft(const sigf_vec& signal, sigc_vec& response)
{
    float N = response.size();

    cout << "N = " << N << "\n\n";

    for (int k = 0; k < response.size(); ++k)
    {
        response[k] = SIG_ZERO;

        for (int n = 0; n < signal.size(); ++n)
        {
            sigf rho   = SIG_ONE;
            sigf theta = 2*M_PI * k / N * -n;

            sigc Z = polar(rho, theta);

            cout << "k = " << k << "\t";
            cout << "n = " << n << "\t";
            cout << "Z = ";

            if (Z.real() >= SIG_ZERO)
            {
                if (Z.imag() >= SIG_ZERO)
                    cout << "negateNone(";
                else
                    cout << "negateImag(";
            }
            else
            {
                if (Z.imag() >= SIG_ZERO)
                    cout << "negateReal(";
                else
                    cout << "negateBoth(";
            }

            cout << fabsf(Z.real()) << " + ";
            cout << fabsf(Z.imag()) << "i)\n";

            response[k] += signal[n] * Z;
        }

        cout << "\n";
    }
}

int main(int argc, const char* argv[])
{
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

    // sigf_vec signal;
    // sigc_vec response;
    //
    // signal.resize(windowSize);
    // response.resize(windowSize);
    //
    // dft(signal, response);

    int N = windowSize;

    for (int n = 0; n < N; ++n)
    {
        for (int k = 0; k < N; ++k)
        {
            int Z = (n * k) % N;

            cout << "k = " << k << "\t";
            cout << "n = " << n << "\t";
            cout << "Z = " << Z << "\n";
        }

        cout << "\n";
    }

    return 0;
}
