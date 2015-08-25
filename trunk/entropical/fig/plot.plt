set term postscript eps color  solid enhanced  size 7,4.9 font ",32"
set output "entropy.eps"

set multiplot
set border lw 3
set xrange [0:1.2]
set key top left
set xlabel ""

plot 0.5*log(1+(2.71828/x)**2) w l lw 3 title "schltter entropy",\
x/(exp(x)-1) -log(1-exp(-x)) w l lw 3 title "Quantum entropy",\
(1-log(x)) w l lw 3 title "classical thermo",\
(-log(x)+log(sqrt(2*pi*2.71828))) w l lw 3 title "classical Gaussian",\
0 w l lt 0 notitle

unset tics
unset xtics
unset ytics
unset key

set tmargin 0
set bmargin 0
set rmargin 0
set lmargin 0
set size 0.3
set origin 0.6,0.6
set xrange [1.2:15]
set yrange [-0.1:1.2]
set xtics 3
set ytics 0.5
set border lw 2
set font ",24"
plot 0.5*log(1+(2.71828/x)**2) w l lw 3 title "schltter entropy",\
x/(exp(x)-1) -log(1-exp(-x)) w l lw 3 title "Quantum entropy"
unset multiplot
