set terminal png 
set title "Ricerca ordine di integrazione algoritmo"
set output "Immagini/ordine/consVerletVelocity.png"
set log xy
set xlabel "dt"
set ylabel "dE"
set format y "10^{%L}"
set format x "10^{%L}"
set grid
f(x)= a * x + b
fit f(x) "data/err.dat" using (log($1)):(log($2)) via a, b
plot "data/err.dat" u 1:2 w p title "dE(dt)", x, x**2 ,x**3 , x**4 , x**5  
reset