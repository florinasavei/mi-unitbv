#importam functiile din numpy
from numpy import dot, zeros

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

#descompunere LU doolitle
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

#metodata de eliminare doolitle
def rezdoolite(a,b):
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