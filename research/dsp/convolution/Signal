set terminal png size 800,600
set output 'Signal.png'
set xlabel "Samples"
set ylabel "Amplitude"
unset logscale x
unset logscale y
set xr [0:2048]
set yr [-2:2]
set style line 100 lt 1 lc rgb "gray" lw 1
set grid xtics ytics mxtics mytics ls 100
plot 'inputRe' title "Input Real Signal" with lines,\
     'inputIm' title "Input Imag Signal" with lines,\
     'ampMod'  title "Amplitude Modulation" with lines,\
     'freqMod' title "Frequency Modulation" with lines,\

     #'output' title "Output Signal" with lines,\
     #'t-var'  title "Time Variant"  with lines
