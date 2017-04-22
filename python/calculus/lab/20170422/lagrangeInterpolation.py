from algoFunctions import lagrangeInterpolation

points = {1.0:1.1, 2.0:4.0, 4.0:16.0, 3.0:9.0}
Y=lagrangeInterpolation(points , 2.5)
print(Y)