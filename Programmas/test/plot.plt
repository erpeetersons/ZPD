set encoding utf8
set xlabel "{/Symbol f}"
set yrange[10:70]
set xrange[0:0.02]
set ylabel "A"
set title ""
unset key
plot 'output.txt' w l lw 2 title "E({/Symbol q})", 0 lw 1 title ""
pause mouse