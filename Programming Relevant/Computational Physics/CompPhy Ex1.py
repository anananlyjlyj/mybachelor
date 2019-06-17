
# a)
import numpy as np
import matplotlib.pyplot as plt

n = [1, 5, 10, 20, 30, 50]
a = 5
x = np.linspace(0, 1, 1e7)
for i in range(0, 5):
    plt.plot(x, x**n[i] / (x + a))
    
# b)
import math
import numpy as np

def f(a, n0, n1, y0):
    yn = np.zeros(np.absolute(n1 - n0) + 1)
    yn0 = y0
    if n0 > 0:
        for j in range(1, n0 + 1):
            yn0 = 1 / j - a * yn0
    yn[0] = yn0
    if n1 > n0:
        for k in range(n0 + 1, n1 + 1):
            yn[k - n0] = 1 / k - a * yn[k - n0 - 1]
    if n1 < n0:
        for l in range(n0 + 1, n1 + 1, -1):
            yn[l - n0] = (1 / l - yn[l - n0 - 1]) / a
    return yn

# c)
print (f(5, 0, 30, math.log(((1 + 5) / 5) )))
x = float(input("Set y0: "))
print (f(5, 50, 30, x))
