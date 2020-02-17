#!/usr/bin/gnuplot -persist
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ms)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set datafile separator ","

set title "Basic Sorts (comparison)" font "Monospace Bold, 14"
set output "./q1-plots/q1-graph.png"
plot "./q1-data-output/q1a-data-sort-selection.csv" with lines lt 3 lw 2 linecolor 6,\
     "./q1-data-output/q1a-data-sort-selection.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./q1-data-output/q1b-data-sort-insertion.csv" with lines lt 3 lw 2 linecolor 1,\
     "./q1-data-output/q1b-data-sort-insertion.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./q1-data-output/q1c-data-sort-bubble.csv" with lines lt 3 lw 2 linecolor 2,\
     "./q1-data-output/q1c-data-sort-bubble.csv" with points lc rgb "black" pointtype 6 pointsize 1

set title "Selection Sort" font "Monospace Bold, 14"
set output "./q1-plots/q1a-graph-sort-selection.png"
plot "./q1-data-output/q1a-data-sort-selection.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q1-data-output/q1a-data-sort-selection.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.0000010 * x**2 lt 1 lw 2 linecolor 6,\
     0.0000012 * x**2 lt 1 lw 2 linecolor 2

set title "Insertion Sort" font "Monospace Bold, 14"
set output "./q1-plots/q1b-graph-sort-insertion.png"
plot "./q1-data-output/q1b-data-sort-insertion.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q1-data-output/q1b-data-sort-insertion.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.00000052 * x**2 lt 1 lw 2 linecolor 6,\
     0.00000060 * x**2 lt 1 lw 2 linecolor 2

set title "Bubble Sort" font "Monospace Bold, 14"
set output "./q1-plots/q1c-graph-sort-bubble.png"
plot "./q1-data-output/q1c-data-sort-bubble.csv" with lines lt 3 lw 2 linecolor 7,\
     "./q1-data-output/q1c-data-sort-bubble.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     0.0000024 * x**2 lt 1 lw 2 linecolor 6,\
     0.0000028 * x**2 lt 1 lw 2 linecolor 2
