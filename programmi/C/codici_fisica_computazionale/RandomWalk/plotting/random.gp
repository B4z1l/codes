
set term png size 1920, 1080 enhanced font "Sans, 20"
set output "img/traiettorie2d.png"
set xlabel "x"
set ylabel "y"
plot "data/out2d.dat" u 6:8 pt 7 ps 0.6 notitle
reset


set term png size 1920, 1080 enhanced font "Sans, 20"
set output "img/traiettorie1d.png"
set xlabel "t"
set ylabel "y"
plot "data/out1d.dat" u 4:6 pt 7 ps 0.6 notitle
reset


# 1D
set term png size 1920, 1080 enhanced font "Sans,20"
set output "img/d2_vs_t1D.png"
set xlabel "t"
set ylabel "d*d"
set log xy
f(x) = m*x + c
fit f(x) 'data/xt.dat' u 1:2 via m, c
plot "data/xt.dat", x, m*x +c title "fit"


# 2D
set term png size 1920, 1080 enhanced font "Sans,20"
set output "img/d2_vs_t2D.png"
set xlabel "t"
set ylabel "d*d"
set log xy
f(x) = m*x + c
fit f(x) 'data/xt2d.dat' u 1:2 via m, c
plot "data/xt2d.dat", x, m*x +c title "fit"

set term png size 1920, 1080 enhanced font "Sans,20"
set output "img/distribuzione_posizioni_finali_2D.png"
unset log xy
set xlabel "x finale"
set ylabel "y finale"
set zlabel "Probabilita' "
splot "data/px2d.dat" with boxes
pause mouse keypress



