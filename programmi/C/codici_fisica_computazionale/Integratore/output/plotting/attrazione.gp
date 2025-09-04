set terminal png size 1520,1320
set title "Bacini di attrazione ad f0 = 1.50"
set output "C:Immagini/attrazione/attrazione_t93f150.png"
set xlabel "α"
set ylabel "dα/dt"
set grid
unset key
set palette defined (-1.5 "black", 1.5 "yellow")
plot "data/attrazione.dat" u 1:2:3 w d palette z
reset

