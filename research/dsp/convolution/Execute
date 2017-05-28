#! /bin/bash

make
echo ""

Convolution inputRe > inputRe
Convolution inputIm > inputIm
Convolution ampMod > ampMod
Convolution freqMod > freqMod

#Convolution output > output
#Convolution response > response
#Convolution t-var > t-var

echo "Generated data files."
echo ""

gnuplot Signal
#gnuplot Spectrum

echo "PNG files created with gnuplot."
echo ""
