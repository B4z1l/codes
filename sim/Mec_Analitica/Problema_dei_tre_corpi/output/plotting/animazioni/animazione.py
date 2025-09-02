import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from matplotlib import animation as ani

ax = plt.axes(projection ='3d')

data = np.loadtxt('C:\\Users\\Nicola\\Desktop\\Programmi\\C\\Problema_dei_tre_corpi\\output\\plotting\\data\\keplero.txt')
for column in data.T:
  
  t = data.T[0]

  x1 = data.T[1]
  y1 = data.T[2]
  z1 = data.T[3]

  x2 = data.T[4]
  y2 = data.T[5]
  z2 = data.T[6]

  x3 = data.T[7]
  y3 = data.T[8]
  z3 = data.T[9]

  ax.plot3D(x1, y1,z1)
  ax.plot3D(x2, y2,z2)
  ax.plot3D(x3, y3,z3)
 


plt.xlabel("X")
plt.ylabel("Y")


plt.title("Simulazione problema dei tre corpi")

plt.show()                      

