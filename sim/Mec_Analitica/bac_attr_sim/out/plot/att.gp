set terminal png size 900,800
set title "Bacini di attrazione ad f0 = 1.35, tmax = 0 ms"
set output "/home/bazil/Documents/codes/bac_attr_sim/out/plot/img/att_t0.png"
set xlabel "α"
set ylabel "dα/dt"
set grid 
unset key
set palette defined (-1.5 "black", 1.5 "red")
plot "/home/bazil/Documents/codes/bac_attr_sim/out/plot/data.txt" u 1:2:3 w d palette z
reset
