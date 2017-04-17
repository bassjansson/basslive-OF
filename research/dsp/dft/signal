set terminal png size 1024,768
set output 'signal.png'
set xlabel "samples"
set ylabel "amplitude"
unset logscale x
unset logscale y
set xr [0:511]
set yr [-1.25:1.25]
set style line 100 lt 1 lc rgb "gray" lw 1
set grid xtics ytics mxtics mytics ls 100
plot 'input'  title "Input Signal"  with lines, \
     'output' title "Output Signal" with lines
