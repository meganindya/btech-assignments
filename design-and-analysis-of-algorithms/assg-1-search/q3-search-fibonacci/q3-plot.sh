#!/usr/bin/gnuplot -persist
set title "Fibonacci Search" font "Monospace Bold, 14"
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ns)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set output "q3-graph.png"
set datafile separator ","
plot "q3-data.csv" with lines lt 3 lw 2 linecolor 7,\
     "q3-data.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     140 * log(x) lt 1 lw 2 linecolor 6,\
     200 * log(x) lt 1 lw 2 linecolor 2
