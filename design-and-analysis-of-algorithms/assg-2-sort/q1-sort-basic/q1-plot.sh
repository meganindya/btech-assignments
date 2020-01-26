#!/usr/bin/gnuplot -persist
set title "Basic Sort" font "Monospace Bold, 14"
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ms)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set output "q1-graph.png"
set datafile separator ","
plot "./data-output/q1a-data-sort-selection.csv" with lines lt 3 lw 2 linecolor 6,\
     "./data-output/q1a-data-sort-selection.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./data-output/q1b-data-sort-insertion.csv" with lines lt 3 lw 2 linecolor 1,\
     "./data-output/q1b-data-sort-insertion.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./data-output/q1c-data-sort-bubble.csv" with lines lt 3 lw 2 linecolor 2,\
     "./data-output/q1c-data-sort-bubble.csv" with points lc rgb "black" pointtype 6 pointsize 1
