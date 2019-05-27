import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve_banded


def euler(f, n, a, b, xa):
    result = np.empty((n + 1,))
    h = (b - a) / n
    x = xa
    t = a
    for i in range(n):
        result[i] = x
        x = x + h * f(t, x)
        t = t + h
    result[n] = x
    return result


