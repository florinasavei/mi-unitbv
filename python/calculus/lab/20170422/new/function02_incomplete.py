import math
def secant(f,a,b,TOL=1e-3,NMAX=100):
    n=1
    while n<NMAX:
        x=a-f(a)/(f(b)-f(a))*(b-a)
        print('x= ',x)
        print('a= ',a)
        print('b= ',b)
        print('f(a)')
        

        if abs(f(x))<TOL:
            return x
        if f(a)*f(x)<0:
            b=x
        else:
            a=x
        n=n+1

    return false


def f(x):
    return (x ** 3) - (10 * (x ** 2)) + 5

