set terminal png size 1920, 1080
set title "Grafico di f(x)"
set output "img/plot.png"
set xlabel "x"
set ylabel "f(x)"
set grid
plot "data/plt.dat" u 1:2 w l notitle
reset 
