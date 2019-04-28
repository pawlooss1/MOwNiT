from functions import *
import pandas as pd


def exercise_newton(a, b, n, eukl_err, max_err):
    plot_name = 'Newton, węzły równoodległe, n=' + repr(n)
    print(plot_name)
    x_inter, x_print, y_inter, y_print, p_print = interpolate_newton(a, b, n)
    eukl_norm, max_norm = calculate_errors(y_print, p_print)
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm
    print_errors(eukl_norm, max_norm)
    print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name)


def exercise_lagrange(a, b, n, eukl_err, max_err):
    plot_name = 'Lagrange, węzły równoodległe, n=' + repr(n)
    print(plot_name)
    x_inter, x_print, y_inter, y_print, p_print = interpolate_lagrange(a, b, n)
    eukl_norm, max_norm = calculate_errors(y_print, p_print)
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm
    print_errors(eukl_norm, max_norm)
    print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name)


def exercise_newton_ch(a, b, n, eukl_err, max_err):
    plot_name = 'Newton, węzły Czebyszewa, n=' + repr(n)
    print(plot_name)
    x_inter, x_print, y_inter, y_print, p_print = interpolate_newton_ch(a, b, n)
    eukl_norm, max_norm = calculate_errors(y_print, p_print)
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm
    print_errors(eukl_norm, max_norm)
    print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name)


def exercise_lagrange_ch(a, b, n, eukl_err, max_err):
    plot_name = 'Lagrange, węzły Czebyszewa, n=' + repr(n)
    print(plot_name)
    x_inter, x_print, y_inter, y_print, p_print = interpolate_lagrange_ch(a, b, n)
    eukl_norm, max_norm = calculate_errors(y_print, p_print)
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm
    print_errors(eukl_norm, max_norm)
    print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name)


def exercise():
    a = -np.pi
    b = 2 * np.pi

    eukl_errors = {}
    max_errors = {}
    for i in range(2, 11):
        exercise_lagrange(a, b, i, eukl_errors, max_errors)
    for i in range(15, 31, 5):
        exercise_lagrange(a, b, i, eukl_errors, max_errors)
    d = {'Eukl': eukl_errors, 'Max': max_errors}
    lagrange_errors = pd.DataFrame(d)

    eukl_errors = {}
    max_errors = {}
    for i in range(2, 11):
        exercise_newton(a, b, i, eukl_errors, max_errors)
    for i in range(15, 31, 5):
        exercise_newton(a, b, i, eukl_errors, max_errors)
    d = {'Eukl': eukl_errors, 'Max': max_errors}
    newton_errors = pd.DataFrame(d)

    eukl_errors = {}
    max_errors = {}
    for i in range(2, 11):
        exercise_lagrange_ch(a, b, i, eukl_errors, max_errors)
    for i in range(15, 31, 5):
        exercise_lagrange_ch(a, b, i, eukl_errors, max_errors)
    d = {'Eukl': eukl_errors, 'Max': max_errors}
    lagrange_ch_errors = pd.DataFrame(d)

    eukl_errors = {}
    max_errors = {}
    for i in range(2, 11):
        exercise_newton_ch(a, b, i, eukl_errors, max_errors)
    for i in range(15, 31, 5):
        exercise_newton_ch(a, b, i, eukl_errors, max_errors)
    d = {'Eukl': eukl_errors, 'Max': max_errors}
    newton_ch_errors = pd.DataFrame(d)
    return lagrange_errors, newton_errors, lagrange_ch_errors, newton_ch_errors
