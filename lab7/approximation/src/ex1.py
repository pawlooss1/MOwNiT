from functions import *


def exercise_polynomial(m):
    a = -np.pi
    b = 2 * np.pi
    eukl_errors = {}
    max_errors = {}
    for n in range(10, 51, 10):
        eukl_n, max_n = exercise(a, b, n, m, simple_wage, monomial_base)
        eukl_errors[n] = eukl_n
        max_errors[n] = max_n
    polynomial_errors = {'Eukl': eukl_errors, 'Max': max_errors}
    return polynomial_errors


def exercise_1():
    errors = {}
    for m in range(1, 5):
        errors[m] = exercise_polynomial(m)
    return errors
