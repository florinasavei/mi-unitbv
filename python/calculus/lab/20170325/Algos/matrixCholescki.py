from numpy import matrix, dot

from algoFunctions import cholescki, rezCholescki
a = matrix([[1.00,2.00,1.0],[2.0,5.00,2.0],[1.0,2.0,3.0]])
b = matrix([[5.0],[11.0],[7.0]])
L=cholescki(a)
x=rezCholescki(L,b)
print(L)
print(x)
