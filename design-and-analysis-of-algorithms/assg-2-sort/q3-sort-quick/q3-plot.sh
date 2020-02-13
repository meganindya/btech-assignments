#!/usr/bin/gnuplot -persist
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ms)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set datafile separator ","

set title "Quick Sort (comparison)" font "Monospace Bold, 14"
set output "./q3-plots/q3-graph.png"
plot "./q3-data-output/q3a-data-sort-quick-org.csv" with lines lt 3 lw 2 linecolor 6,\
     "./q3-data-output/q3a-data-sort-quick-org.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./q3-data-output/q3b-data-sort-quick-mod.csv" with lines lt 3 lw 2 linecolor 2,\
     "./q3-data-output/q3b-data-sort-quick-mod.csv" with points lc rgb "black" pointtype 6 pointsize 1

set title "Quick Sort (original)" font "Monospace Bold, 14"
set output "./q3-plots/q3a-graph-sort-quick-org.png"
plot "./q3-data-output/q3a-data-sort-quick-org.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q3-data-output/q3a-data-sort-quick-org.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.000010 * x * log(x) lt 1 lw 2 linecolor 6,\
     0.000013 * x * log(x) lt 1 lw 2 linecolor 2

set title "Quick Sort (random pivot)" font "Monospace Bold, 14"
set output "./q3-plots/q3b-graph-sort-quick-mod.png"
plot "./q3-data-output/q3b-data-sort-quick-mod.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q3-data-output/q3b-data-sort-quick-mod.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.000010 * x * log(x) lt 1 lw 2 linecolor 6,\
     0.000014 * x * log(x) lt 1 lw 2 linecolor 2
