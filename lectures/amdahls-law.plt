#!/ust/bin/gnuplot -persist

set title "Amdahl's Law"
set output "amdahls-law.pdf"
set terminal pdfcairo solid color enhanced

set logscale x 2
set yrange[0:20]
set ytics 1
set xrange[1:65536]
set grid
set ylabel "Speedup" font "Times-Roman,14"
set xlabel "Number of Processors" font "Times-Roman,14"

s(p, alpha) = 1 / (alpha + (1 - alpha) / p)

set key title "Parallel Portion"

plot s(x, 0.05) title "95%",    \
     s(x, 0.1) title "90%",     \
     s(x, 0.25) title "75%",    \
     s(x, 0.5) title "50%"
