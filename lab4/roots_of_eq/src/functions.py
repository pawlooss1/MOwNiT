import numpy as np


def newton1(f, f_1, x, nmax, epsilon):
    fx = f(x)
    for n in range(0, nmax):
        x_old = x
        fp = f_1(x)
        d = fx / fp
        x = x - d
        fx = f(x)
        if abs(x - x_old) < epsilon:
            return x, n, fx
    return 'nie zbieżne', 'nie zbieżne', 'nie zbieżne'


def newton2(f, f_1, x, nmax, epsilon):
    fx = f(x)
    for n in range(0, nmax):
        fp = f_1(x)
        d = fx / fp
        x = x - d
        fx = f(x)
        if abs(fx) < epsilon:
            return x, n, fx
    return 'nie zbieżne', 'nie zbieżne', 'nie zbieżne'


def secant1(f, a, b, nmax, epsilon):
    fa = f(a)
    fb = f(b)
    if abs(fa) > abs(fb):
        a, b = b, a
        fa, fb = fb, fa
    for n in range(0, nmax):
        if abs(fa) > abs(fb):
            a, b = b, a
            fa, fb = fb, fa
        d = (b - a) / (fb - fa)
        b = a
        fb = fa
        d = d * fa
        a = a - d
        fa = f(a)
        if abs(a - b) < epsilon:
            return a, n, fa
    return 'nie zbieżne', 'nie zbieżne', 'nie zbieżne'


def secant2(f, a, b, nmax, epsilon):
    fa = f(a)
    fb = f(b)
    if abs(fa) > abs(fb):
        a, b = b, a
        fa, fb = fb, fa
    for n in range(0, nmax):
        if abs(fa) > abs(fb):
            a, b = b, a
            fa, fb = fb, fa
        d = (b - a) / (fb - fa)
        b = a
        fb = fa
        d = d * fa
        a = a - d
        fa = f(a)
        if abs(fa) < epsilon:
            return a, n, fa
    return 'not convergence', 'nie zbieżne', 'nie zbieżne'


def apply_func_vect(F, X):
    X = X.transpose().tolist()[0]
    rows, cols = F.shape
    F_X = []
    for i in range(rows):
        for j in range(cols):
            F_X.append(F[i][j](*X))
    return np.array(F_X).reshape(F.shape)


def newton_system1(F, J, X, epsilon):
    for i in range(100):
        F_X = apply_func_vect(F, X)
        J_X = apply_func_vect(J,X)
        H = np.linalg.solve(J_X, F_X)
        X = X - H
        if np.linalg.norm(H) < epsilon:
            return X, i
    return 'nie zbieżne', 100


def newton_system2(F, J, X, epsilon):
    for i in range(100):
        F_X = apply_func_vect(F, X)
        J_X = apply_func_vect(J,X)
        H = np.linalg.solve(J_X, F_X)
        X = X - H
        if np.linalg.norm(F_X) < epsilon:
            return X, i
    return 'nie zbieżne', 100
