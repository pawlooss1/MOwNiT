import numpy as np
import matplotlib.pyplot as plt

POINTS = 500


def f(x):
    return np.sin(2*x) * np.sin(x**2/np.pi)


def monomial_base(i):
    return lambda x: x**i


def calculate_matrix_elem(row, col, x_arr, wage_fun, base_generator):
    fi_k = base_generator(row)
    fi_j = base_generator(col)
    return np.sum(wage_fun(x_arr) * fi_k(x_arr) * fi_j(x_arr))


def calculate_vector_elem(row, x_arr, y_arr, wage_fun, base_generator):
    fi_k = base_generator(row)
    return np.sum(wage_fun(x_arr) * y_arr * fi_k(x_arr))


def generate_eq_sys_matrix(m, x_arr, wage_fun, base_generator):
    result = np.empty((m,m))
    for i in range(m):
        for j in range(m):
            result[i][j] = calculate_matrix_elem(i, j, x_arr, wage_fun, base_generator)
    return result


def generate_eq_sys_dependent_vector(m, x_arr, y_arr, wage_fun, base_generator):
    result = np.empty((m,))
    for i in range(m):
        result[i] = calculate_vector_elem(i, x_arr, y_arr, wage_fun, base_generator)
    return result


def compute_a_coeff(m, x_arr, y_arr, wage_fun, base_generator):
    g = generate_eq_sys_matrix(m, x_arr, wage_fun, base_generator)
    b = generate_eq_sys_dependent_vector(m, x_arr, y_arr, wage_fun, base_generator)
    return np.linalg.solve(g, b)


def print_errors(y_print, p_print):
    print('Błąd interpolacji(norma euklidesowa):', np.linalg.norm(y_print-p_print) / POINTS)
    print('Błąd interpolacji(norma maksimum):', np.linalg.norm(y_print-p_print, ord=np.inf))


def print_plots(x_approx, x_print, y_approx, y_print, p_print):
    fig = plt.figure()
    ax = fig.add_axes([0, 0, 1, 1])
    ax.plot(x_print, p_print, label="W(x)")
    ax.plot(x_print, y_print, label="f(x)")
    ax.plot(x_approx, y_approx, '*', label='Węzły aproksymacji')
    ax.set_title('elo')
    ax.set_ylabel('y')
    ax.set_xlabel('x')
    ax.legend()
    plt.show()


def evaluate_approximation_polynomial(x, a_coeff, base):
    m = len(a_coeff)
    values = [] #np.empty((m,))
    for i in range(m):
        monomial = base(i)
        value = a_coeff[i] * monomial(x)
        values.append(value) # = evaluate_fun(monomial, x)
    return sum(values)


def approximate(m, x_print, x_approx, y_approx, wage_fun, base_generator):
    a = compute_a_coeff(m, x_approx, y_approx, wage_fun, base_generator)
    return evaluate_approximation_polynomial(x_print, a, base_generator)


def exercise(a, b, n, m):
    m = m + 1
    print("Stopień wielomianu: {0:d}, liczba węzłów: {1:d}".format(m, n))
    x_approx = np.linspace(a, b, n)
    x_print = np.linspace(a, b, POINTS)
    y_approx = f(x_approx)
    y_print = f(x_print)
    p_print = approximate(m, x_print, x_approx, y_approx, wage_fun=lambda x: 1, base_generator=monomial_base)
    print_errors(y_print, p_print)
    print_plots(x_approx, x_print, y_approx, y_print, p_print)
