set term png font "Times,12"
set encoding utf8
set output "output.png"
set xlabel "{/Symbol q}"
set ylabel "E"
set title "{/Symbol q f}"
# unset key
plot 'output.txt' w l lw 2 title "E({/Symbol q})", 0 lw 1 title ""
