#!/usr/bin/gnuplot -persist
set title "Sequential Search" font "Monospace Bold, 14"
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ns)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set output "q1a-graph.png"
set datafile separator ","
plot "q1a-data.csv" with lines lt 3 lw 2 linecolor 7,\
     "q1a-data.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     2.08 * x lt 1 lw 2 linecolor 6,\
     2.25 * x lt 1 lw 2 linecolor 2
