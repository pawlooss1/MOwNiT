import numpy as np
import matplotlib.pyplot as plt

POINTS = 500


def f(x):
    return np.sin(2*x) * np.sin(x**2/np.pi)


def simple_wage(x):
    return 1


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


def calculate_errors(y_print, p_print):
    eukl_norm = np.linalg.norm(y_print - p_print) / POINTS
    max_norm = np.linalg.norm(y_print - p_print, ord=np.inf)
    return eukl_norm, max_norm


def print_errors(eukl, max):
    print('Błąd interpolacji(norma euklidesowa):', eukl)
    print('Błąd interpolacji(norma maksimum):', max)


def print_plots(x_approx, x_print, y_approx, y_print, p_print, plot_name):
    fig, ax = plt.subplots()
    ax.plot(x_print, p_print, label="W(x)")
    ax.plot(x_print, y_print, label="f(x)")
    ax.plot(x_approx, y_approx, '*', label='Węzły interpolacji')
    ax.set_title(plot_name)
    ax.set_ylabel('y')
    ax.set_xlabel('x')
    ax.legend()
    plt.tight_layout()
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


def exercise(a, b, n, m, wage, base):
    plot_name = "Stopień wielomianu: {0:d}, liczba węzłów: {1:d}".format(m, n)
    m = m + 1
    print(plot_name)
    x_approx = np.linspace(a, b, n)
    x_print = np.linspace(a, b, POINTS)
    y_approx = f(x_approx)
    y_print = f(x_print)
    p_print = approximate(m, x_print, x_approx, y_approx, wage_fun=wage, base_generator=base)
    eukl_n, max_n = calculate_errors(y_print, p_print)
    print_errors(eukl_n, max_n)
    print_plots(x_approx, x_print, y_approx, y_print, p_print, plot_name)
    return eukl_n, max_n
