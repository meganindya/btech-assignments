set terminal png size 800, 800 enhanced font "Helvetica, 10"
set output 'memory.png'
set palette rgbformulae 33, 13, 10
set pm3d
set zlabel 'throughput'
set ylabel 'stride (x8 bytes)'
set xlabel 'size (bytes)'
splot 'results.csv' matrix with lines
