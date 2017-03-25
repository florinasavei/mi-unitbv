from numpy import matrix
from functiiAlgli import rezgauss
a = matrix([[4.0,-2.0,1.0],[-2.0,4.0,-2.0],[1.0,-2.0,4.0]])
b = matrix([[11.0],[-16.0],[17.0]])
print(rezgauss(a,b))