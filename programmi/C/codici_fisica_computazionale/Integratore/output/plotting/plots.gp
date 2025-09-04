


# A = 1.414213 e φ = -0.78539816 per w2 = x0 = v0 = 1 cambiare se necessario
set terminal png size 1000, 700
set title "Traiettoria oscillatore "
set output "C:Immagini/algoritmi/rounge_kutta4/x(t)_rk4.png"
set xlabel "t"
set ylabel "x(t)"
set grid
set samples 10000
plot "data/dati.dat" u 1:2 w l notitle , 1.414213*cos(x-0.78539816) title "Acos(x-φ)" 
reset 


set terminal png size 1000, 700
set title "Velocità oscillatore"
set output "C:Immagini/algoritmi/rounge_kutta4/v(t)_rk4.png"
set xlabel "t"
set ylabel "v(t)"
set grid
plot "data/dati.dat" u 1:3 w l notitle 
reset 




set terminal png size 1000, 700
set title "Spazio delle fasi"
set output "C:Immagini/algoritmi/rounge_kutta4/Spazio_Fasi_rk4.png"
set xlabel "x(t)"
set ylabel "v(t)"
set grid
plot "data/dati.dat" u 2:3 w l notitle 
reset 


set terminal png size 1000, 700
set title "Energia"
set output "C:Immagini/algoritmi/rounge_kutta4/Energia_rk4.png"
set xlabel "t"
set ylabel "dE(t)"
set grid
plot "data/dati.dat" u 1:4 w l notitle 
reset 
