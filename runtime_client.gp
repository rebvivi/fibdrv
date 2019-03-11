reset
set ylabel 'time(ns)'
set xlabel 'size'
set xtics 0, 10
set title 'runtime 0(logn)'
set term png enhanced font 'Verdana,10'

set output 'runtime_comparison_11.png'

plot [:][:500]'output2.txt' \
   using 1:2 with linespoints linewidth 3  title 'user', \
'' using 1:3 with linespoints linewidth 3 title 'kernel' , \
'' using 1:4 with linespoints linewidth 3 title 'kernel to user' , \





