#!/ust/bin/gnuplot -persist

set title "Amdahl's Law"
set output "amdahls-law.pdf"
set terminal pdfcairo solid color enhanced

set logscale x 2
set yrange[0:20]
set xrange[1:65536]
set grid
set ylabel "Speedup" font "Times-Roman,14"
set xlabel "Number of Processors" font "Times-Roman,14"

s(p, alpha) = 1 / (alpha + (1 - alpha) / p)

plot s(x, 0.05), \
     s(x, 0.1),  \
     s(x, 0.25), \
     s(x, 0.5)
