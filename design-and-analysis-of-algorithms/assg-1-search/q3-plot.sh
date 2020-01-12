#!/usr/bin/gnuplot -persist
set title "Fibonacci Search" font "Helvetica Bold, 14"
set xlabel "array size (n)"
set ylabel "iterations"
set grid
set terminal png size 1024,768
set output 'q3-graph.png'
set datafile separator ','
#plot 'q2.csv' with points pointtype 7 pointsize 0.2
plot 'q3-data.csv' u 1:2 smooth bezier
