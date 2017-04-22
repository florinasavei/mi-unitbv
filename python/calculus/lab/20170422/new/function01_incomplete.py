from math import ceil
from numpy import log


def f(x):
    return (x ** 3) - (10 * (x ** 2)) + 5


def bisect(f, a, b, tol):
    n = ceil(log(abs(b - a)) / log(2))

    if f(a) == 0.0:
        rad = a
    if f(b) == 0.0:
        rad = b

    for i in range(1,tol):
        print('iteratin ' + str(i))
        if f(a) * f(b) > 0.0:
            print('nu e radagina')
    else:
        m = (a + b) / 2.0
        if f(m)==0.0 :
            return m
        if (f(a) * f(m) < 0.0):
            b = m
        else:
            a = m

    return m


print(bisect(f, 0.6, 0.8, 4))
