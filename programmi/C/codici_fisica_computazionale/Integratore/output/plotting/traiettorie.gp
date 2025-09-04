set terminal png size 1000,800 enhanced
set title "Traiettorie forzante diverso"
set output "C:Immagini/traiettorie/traiettorie.png"
set xlabel "t"
set ylabel "x(t)"
set grid
plot "data/x1.dat" u 1:2 w d notitle, "data/x2.dat" u 1:2 w d notitle, "data/x3.dat" u 1:2 w d notitle  , "data/x4.dat" u 1:2 w d notitle  , "data/x5.dat" u 1:2 w d notitle        
reset