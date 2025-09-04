set terminal png size 800,600 enhanced
set title "Diagrammi di biforcazione"
set output "C:Immagini/biforcazioni/biforcazione.png"
set xlabel "a0 (ampiezza forzante)"
set ylabel "v finale"
#set zlabel "x finale"
set grid
plot "data/biforcazione.dat" u 1:2 w d notitle #"biforcazione2.dat" u 1:2 w d notitle, "biforcazione3.dat" u 1:2 w d notitle, "biforcazione4.dat" u 1:2 w d notitle, "biforcazione5.dat" u 1:2 w d notitle, "biforcazione6.dat" u 1:2 w d notitle, "biforcazione7.dat" u 1:2 w d notitle, "biforcazione8.dat" u 1:2 w d notitle , "biforcazione9.dat" u 1:2 w d notitle , "biforcazione10.dat" u 1:2 w d notitle  , "biforcazione11.dat" u 1:2 w d notitle     
#splot "data/biforcazione.dat" u 1:2:3 w d notitle
reset