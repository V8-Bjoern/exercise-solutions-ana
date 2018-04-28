set terminal postscript eps enhanced color
set output 'plot.eps'
set grid
set title 'Coverage'
set xlabel '{/Symbol m}'
set ylabel 'C({/Symbol m})'
plot "cmu.txt" using 1:2 with points lc rgb "blue"
quit
