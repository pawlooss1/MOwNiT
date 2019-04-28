import numpy as np
import matplotlib.pyplot as plt

POINTS = 500


def lagrange_interpolation(X, Y, x):
    result = 0
    n = len(X)
    for i in range(n):
        li = Y[i]
        for j in range(n):
            if i != j:
                li *= (x - X[j]) / (X[i] - X[j])
        result += li
    return result


def calculate_coefficients(X, Y):
    n = len(X)
    A = np.empty((n, n))
    for i in range(n):
        A[i][0] = Y[i]
    for j in range(1, n):
        for i in range(n - j):
            A[i][j] = (A[i + 1][j - 1] - A[i][j - 1]) / (X[i + j] - X[i])
    return A[0]


def newton_interpolation(X, Y, x):
    result = 0
    n = len(X)
    A = calculate_coefficients(X, Y)
    for i in range(n):
        product = A[i]
        for j in range(i):
            product *= (x - X[j])
        result += product
    return result


def chebyshev_roots(n):
    return np.flip(np.fromfunction(lambda i: np.cos(np.pi * (i + 0.5) / n), (n,)))


def chebyshev_nodes(a, b, n):
    if a > b:
        a, b = b, a
    roots = chebyshev_roots(n)
    stretch = (b - a) / 2
    return (roots + 1) * stretch + a


def f(x):
    return np.sin(2 * x) * np.sin(x ** 2 / np.pi)


def interpolate_lagrange(a, b, n):
    x_inter = np.linspace(a, b, n)
    x_print = np.linspace(a, b, POINTS)
    y_inter = f(x_inter)
    y_print = f(x_print)
    p_print = np.empty(POINTS)
    for i in range(POINTS):
        p_print[i] = lagrange_interpolation(x_inter, y_inter, x_print[i])
    return x_inter, x_print, y_inter, y_print, p_print


def interpolate_newton(a, b, n):
    x_inter = np.linspace(a, b, n)
    x_print = np.linspace(a, b, POINTS)
    y_inter = f(x_inter)
    y_print = f(x_print)
    p_print = np.empty(POINTS)
    for i in range(POINTS):
        p_print[i] = newton_interpolation(x_inter, y_inter, x_print[i])
    return x_inter, x_print, y_inter, y_print, p_print


def interpolate_lagrange_ch(a, b, n):
    x_inter = chebyshev_nodes(a, b, n)
    x_print = np.linspace(a, b, POINTS)
    y_inter = f(x_inter)
    y_print = f(x_print)
    p_print = np.empty(POINTS)
    for i in range(POINTS):
        p_print[i] = lagrange_interpolation(x_inter, y_inter, x_print[i])
    return x_inter, x_print, y_inter, y_print, p_print


def interpolate_newton_ch(a, b, n):
    x_inter = chebyshev_nodes(a, b, n)
    x_print = np.linspace(a, b, POINTS)
    y_inter = f(x_inter)
    y_print = f(x_print)
    p_print = np.empty(POINTS)
    for i in range(POINTS):
        p_print[i] = newton_interpolation(x_inter, y_inter, x_print[i])
    return x_inter, x_print, y_inter, y_print, p_print


def calculate_errors(y_print, p_print):
    eukl_norm = np.linalg.norm(y_print - p_print) / POINTS
    max_norm = np.linalg.norm(y_print - p_print, ord=np.inf)
    return eukl_norm, max_norm


def print_errors(eukl, max):
    print('Błąd interpolacji(norma euklidesowa):', eukl)
    print('Błąd interpolacji(norma maksimum):', max)


def print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name):
    fig, ax = plt.subplots()
    # ax = fig.add_axes([0, 0, 1, 1])
    ax.plot(x_print, p_print, label="W(x)")
    ax.plot(x_print, y_print, label="f(x)")
    ax.plot(x_inter, y_inter, '*', label='Węzły interpolacji')
    ax.set_title(plot_name)
    ax.set_ylabel('y')
    ax.set_xlabel('x')
    ax.legend()
    plt.tight_layout()
    plt.show()
