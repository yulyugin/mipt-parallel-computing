#!/ust/bin/gnuplot -persist

set title "tiny bandwidth == HUGE BOTTLENECK"
set output "memory-wall.pdf"
set terminal pdfcairo solid color enhanced

set yrange[0:4]
set ytics ("0.1" 0, "1" 1, "10" 2, "100" 3, "1000" 4)
set xrange[1975:2010]
set grid
set ylabel "Performance" font "Times-Roman,14"
set xlabel "Year" font "Times-Roman,14"

cpu(x) = 0.25 * x - 496.5
mem(x) = x / 35 - 55.85

set key 1990, 2.8

plot cpu(x) lc rgb 'red' title "CPU Speed", \
     mem(x) lc rgb 'blue' title "Memory Speed"

