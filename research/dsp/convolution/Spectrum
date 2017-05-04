set terminal png size 800,600
set output 'Spectrum.png'
set xlabel "Hz"
set ylabel "dB"
set logscale x
unset logscale y
set xr [20:20000]
set yr [-80:20]
set style line 100 lt 1 lc rgb "gray" lw 1
set grid xtics ytics mxtics mytics ls 100
plot 'response' title "Frequency Response" with lines
