set terminal png size 1920, 1080
set title "Grafico di f(x)"
set output "img/f-F.png"
set xlabel "x"
set ylabel "f'(x)"
set grid
plot "output.dat" u 1:2 w l title "f(x)", "output.dat" u 1:3 w l title "F(x)" 
reset 