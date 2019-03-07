reset
set ylabel 'time(sec)'
set xlabel 'size'
set key left top
set title 'runtime comparison'
set term png enhanced font 'Verdana,10'

set output 'runtime_comparison_client.png'

plot [:][:0.003]'output.txt' \
   using 2:xtic(1) with linespoints linewidth 3 title 'teacher', \
'' using 3:xtic(1) with linespoints linewidth 3 title 'our' , \

   



