#!/usr/bin/gnuplot -persist
set title "Sequential Search" font "Helvetica Bold, 14"
set xlabel "array size (n)"
set ylabel "time (ns)"
set grid
set terminal png size 1024,768
set output 'q1.png'
set datafile separator ','
#plot 'q1.csv' with points pointtype 7 pointsize 0.2
plot 'q1.csv' u 1:2 smooth bezier