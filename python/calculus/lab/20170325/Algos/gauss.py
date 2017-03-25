from numpy import dot, zeros

def rezgauss(a,b):
    n=len(b)
    x=len(b)
    for k in range(0,n-1):
        if a[i,k] !=0.0:
            l=a[i,k]/a[k,]
            a[i,k]=a[i,k]-l*a[k,k]
            a[i,k+1:n]=a[i,k+1:n]-l*a[k,k+1:n]
            b[i]=b[i]-i*b[k]
    for k in range(n-1,-1,-1):
        x[k]=(b[k]-dot(a[k,k+1:n], x[k+1:n]))/a[k,k]
    return x