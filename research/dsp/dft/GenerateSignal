#! /bin/bash

make

echo ""

DFT_Test "input" > input
DFT_Test "output" > output
DFT_Test "response" > response

echo "Generated data files 'input', 'output' and 'response'."
echo ""

gnuplot signal
gnuplot spectrum

echo "PNG files created with gnuplot."
echo ""
