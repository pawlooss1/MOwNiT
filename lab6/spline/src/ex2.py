from functions import *


def exercise_cubic(a, b, n, z0, eukl_err, max_err):
    eukl_norm, max_norm = exercise(a, b, n, z0, spline_type='trzeci')
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm


def exercise_2():
    a = -np.pi
    b = 2 * np.pi

    z0 = 0
    eukl_errors = {}
    max_errors = {}
    for i in range(3, 11):
        exercise_cubic(a, b, i, z0, eukl_errors, max_errors)
    for i in range(15, 51, 5):
        exercise_cubic(a, b, i, z0, eukl_errors, max_errors)
    cubic_natural_errors = {'Eukl': eukl_errors, 'Max': max_errors}
    return cubic_natural_errors
