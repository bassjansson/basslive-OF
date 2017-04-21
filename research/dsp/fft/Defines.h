
#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <complex>
#include <vector>

using namespace std;


// Signal value constants
#define SIG_ZERO 0.0f
#define SIG_ONE  1.0f
#define SIG_TWO  2.0f

// Signal value types
typedef int           SigI;
typedef float         SigF;
typedef complex<SigF> SigC;

// Signal vector types
typedef vector<SigF> SigFVec;
typedef vector<SigC> SigCVec;


#endif /* DEFINES_H */
