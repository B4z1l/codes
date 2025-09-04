
import numpy as np # type: ignore
import matplotlib.pyplot as plt # type: ignore
import scipy as sci  # type: ignore
from mpl_toolkits import mplot3d




agg = 0
u = 5
K =  1e-10/(4 * np.pi* 8.854e-12)
def f(x,y):
    return  K * np.log((x+u+np.sqrt((x+u)**2+y**2))/(x-u+np.sqrt((x-u)**2+y**2))) 


o = 16

x_range = y_range = np.linspace(-o, o, 101)
x ,y = np.meshgrid(x_range, y_range)

dfdy, dfdx = np.gradient(-f(x,y), o/100)# il meno va messo per via della definizione di potenziale: F(r) = -∂U/∂r

a = 2
b = 3
plt.figure(figsize = (5,5))
plt.contour(f(x,y), origin = 'upper', extent = (-o,o,-o,o))
Q = plt.quiver(x[a::b,a::b], y[a::b,a::b], dfdx[a::b,a::b], dfdy[a::b,a::b], pivot = 'middle' )  #[a::b,a::b]

plt.title('Campo vettoriale generato da un dipolo elettrico')
plt.quiverkey(Q, 0.73, 0.76, 1, "CV", labelpos = 'E')
plt.axis('tight')
plt.xlabel('x')
plt.ylabel('y')

plt.plot()
plt.show()




x = np.linspace(-o, o, 100)
y = np.linspace(-o, o, 100)

X, Y = np.meshgrid(x, y)
Z = f(X, Y)

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', rstride = 1, cstride = 1, edgecolor = 'none')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.view_init(45, 200)

plt.show()