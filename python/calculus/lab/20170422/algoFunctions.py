from numpy import dot, zeros, transpose


def interpolation(points, a):
    # sort the x vector
    vecx = sorted(points)
    n = len(vecx)
    # if out fo range - fail with error
    if a < vecx[0] or a > vecx[n - 1]:
        return "X out of range"
    # attempt to find x1 and x2 so that x1< a <=x2
    for i in range(n):
        if vecx[i] >= a:
            x1 = vecx[i - 1]
            x2 = vecx[i]
            y1 = points[x1]
            y2 = points[x2]
            # compute the value for a
            print(x1)
            return y1 + (y2 - y1) / (x2 - x1) * (a - x1)


def lagrangeInterpolation(points, a):
    n = len(points)
    vecx = list(points.keys())
    P = 0
    for j in range(n):
        l = 1
        for i in range(n):
            if i != j:
                l = l * (a - vecx[i]) / (vecx[j] - vecx[i])
        L = l * points[vecx[j]]
    P = P + L
    return P


def newtonInterpolation(points, b):
    x = sorted(points)
    delta = []

    for i in x:
        delta.append(points[i])

    def divizate(x, delta):
        n = len(x)
        for step in range(1, n):
            for i in range(n - 1, step - 1, -1):
                delta[i] = (delta[i] - delta[i - 1]) / (x[i] - x[i - step])
        return delta

    def Eval(delta, x, z):
        n = len(delta) - 1
        pol = delta[n]
        for i in range(n - 1, -1, -1):
            pol = pol * (z - x[i]) + delta[i]
        return pol

    a = divizate(x, delta)
    print(delta)
    rez = Eval(a, x, b)
    return rez


def newtonInterpolation_left(points, b): #incomplete
    x = sorted(points)
    delta = []
    h=x[1]-x[0]

    for i in x:
        delta.append(points[i])

    def divizate(x, delta):
        n = len(x)
        for step in range(n-1,1,-1):
            for i in range(step):
                delta[i] = (delta[i+1]-delta[i])
        return delta

    def Eval(delta, x, z):
        n = len(delta)
        pol = delta[0]
        for i in range(n - 1, 1, -1):
           # pol = pol * (z - x[i]) + delta[i]
            pol=pol*(z-x[n-1])/((i)*h)+delta[n-i]
        return pol

    a = divizate(x, delta)
    print(delta)
    rez = Eval(a, x, b)
    return rez



def newtonInterpolation_right(points, b): #incomplete
    x = sorted(points)
    delta = []
    h=x[1]-x[0]

    for i in x:
        delta.append(points[i])

    def divizate(x, delta):
        n = len(x)
        for step in range(1,n):
            for i in range(n-1,step-1,-1):
                delta[i] = (delta[i]-delta[i-1])
        return delta

    def Eval(delta, x, z):
        n = len(delta)-1
        pol = delta[n]
        for i in range(n - 1, -1, -1):
            pol = pol * (z - x[i])/((i+1)*h) + delta[i]
        return pol

    a = divizate(x, delta)
    print(delta)
    rez = Eval(a, x, b)
    return rez
