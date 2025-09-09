
set terminal png size 1270, 720
set title "Andamento densita per x > 0 (volume) nel tempo"
set output "densita.png"
set xlabel "t [sec]"
set ylabel "D(t) [particelle/m^3]"
set grid
plot "dens.dat" u 1:2 w l
reset
