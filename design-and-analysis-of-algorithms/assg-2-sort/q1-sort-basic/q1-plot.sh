#!/usr/bin/gnuplot -persist
set xlabel "array size (n)" font "Monospace"
set ylabel "time (ms)" font "Monospace"
set key left top
set grid
set terminal png size 1024,768
set datafile separator ","

set title "Basic Sorts (comparison)" font "Monospace Bold, 14"
set output "./plots/q1-graph.png"
plot "./data-output/q1a-data-sort-selection.csv" with lines lt 3 lw 2 linecolor 6,\
     "./data-output/q1a-data-sort-selection.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./data-output/q1b-data-sort-insertion.csv" with lines lt 3 lw 2 linecolor 1,\
     "./data-output/q1b-data-sort-insertion.csv" with points lc rgb "black" pointtype 6 pointsize 1,\
     "./data-output/q1c-data-sort-bubble.csv" with lines lt 3 lw 2 linecolor 2,\
     "./data-output/q1c-data-sort-bubble.csv" with points lc rgb "black" pointtype 6 pointsize 1

set title "Selection Sort" font "Monospace Bold, 14"
set output "./plots/q1a-graph-sort-selection.png"
plot "./data-output/q1a-data-sort-selection.csv" with lines lt 3 lw 2 linecolor 7,\
     "./data-output/q1a-data-sort-selection.csv" with points lc rgb "black" pointtype 6 pointsize 1

set title "Insertion Sort" font "Monospace Bold, 14"
set output "./plots/q1b-graph-sort-insertion.png"
plot "./data-output/q1b-data-sort-insertion.csv" with lines lt 3 lw 2 linecolor 7,\
     "./data-output/q1b-data-sort-insertion.csv" with points lc rgb "black" pointtype 6 pointsize 1

set title "Bubble Sort" font "Monospace Bold, 14"
set output "./plots/q1c-graph-sort-bubble.png"
plot "./data-output/q1c-data-sort-bubble.csv" with lines lt 3 lw 2 linecolor 7,\
     "./data-output/q1c-data-sort-bubble.csv" with points lc rgb "black" pointtype 6 pointsize 1
