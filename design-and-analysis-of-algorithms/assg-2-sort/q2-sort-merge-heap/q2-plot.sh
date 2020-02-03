#!/usr/bin/gnuplot -persist
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ms)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set datafile separator ","

set title "Merge Sort and Heap Sort" font "Monospace Bold, 14"
set output "./q2-plots/q2-graph.png"
plot "./q2-data-output/q2a-data-sort-merge.csv" with lines lt 3 lw 2 linecolor 6,\
     "./q2-data-output/q2a-data-sort-merge.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./q2-data-output/q2b-data-sort-heap.csv" with lines lt 3 lw 2 linecolor 2,\
     "./q2-data-output/q2b-data-sort-heap.csv" with points lc rgb "black" pointtype 6 pointsize 1

set title "Merge Sort" font "Monospace Bold, 14"
set output "./q2-plots/q2a-graph-sort-merge.png"
plot "./q2-data-output/q2a-data-sort-merge.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q2-data-output/q2a-data-sort-merge.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.000013 * x * log(x) lt 1 lw 2 linecolor 6,\
     0.000016 * x * log(x) lt 1 lw 2 linecolor 2

set title "Heap Sort" font "Monospace Bold, 14"
set output "./q2-plots/q2b-graph-sort-heap.png"
plot "./q2-data-output/q2b-data-sort-heap.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q2-data-output/q2b-data-sort-heap.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.000018 * x * log(x) lt 1 lw 2 linecolor 6,\
     0.000021 * x * log(x) lt 1 lw 2 linecolor 2
