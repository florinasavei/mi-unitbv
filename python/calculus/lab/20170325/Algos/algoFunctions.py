#importam functiile din numpy
from numpy import dot, zeros, transpose


#metodata de eliminare Gauss
def rezgauss(a,b):
    n=len(b)
    x=zeros(n)
    for k in range(0,n-1):
        for i in range(k+1,n):
            if a[i,k] !=0.0:
                l = a[i,k]/a[k,k]
                a[i,k]=a[i,k]-l*a[k,k]
                a[i,k+1:n]=a[i,k+1:n]-l*a[k,k+1:n]
                b[i]=b[i]-l*b[k]
    for k in range(n-1,-1,-1):
        x[k]=(b[k]-dot(a[k,k+1:n], x[k+1:n]))/a[k,k]
    return x

#descompunere LU doolitle pentru metoda doolittle
def LUdoolittle(a):
    n=len(a)
    for k in range(0,n-1):
        for i in range(k+1,n):
            if a[i,k] !=0.0:
                l = a[i,k]/a[k,k]
                a[i,k]=a[i,k]-l*a[k,k]
                a[i,k+1:n]=a[i,k+1:n]-l*a[k,k+1:n]
                a[i,k]=l
    return a

#metodata de eliminare doolittle
def rezdoolitte(a,b):
    a=LUdoolittle(a)
    n=len(b)
    x=zeros(n)
    y=b
    for k in range(1,n):
        y[k]=b[k]-dot(a[k,0:k],y[0:k])
    for k in range(n-1,-1,-1):
        x[k]=(b[k]-dot(a[k,k+1:n], x[k+1:n]))/a[k,k]
    return x

from math import sqrt
import sys

def cholescki(a):
    n=len(a)
    for k in range(n):
        if a[k,k] - dot(a[k,0:k],transpose(a[k,0:k]))<0:
            print('Matricea nu este pozitiv definita')
            sys.exit()
        a[k,k]= sqrt(a[k,k] - dot(a[k,0:k],transpose(a[k,0:k])))
        for i in range(k+1,n):
            a[i,k]=(a[i,k]-dot(a[i,0:k],transpose(a[k,0:k])))/a[k,k]
    for k in range(1,n):
        a[0:k,k]=0.0
    return a

def rezCholescki(L,b):
    n=len(b)
    x=zeros(n)
    y=b
    #solution of [L]{y}={b}
    for k in range(n):
        y[k]=(b[k] -dot(L[k,0:k],y[0:k]))/L[k,k]
    #solution of [L_transpsose]{x}={y}
    for k in range(n-1,-1,-1):
        x[k]=(b[k]-dot(transpose(L[k+1:n,k]), x[k+1:n]))/L[k,k]
    return x