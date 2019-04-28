from functions import *
import pandas as pd


def exercise_hermite(a, b, n, eukl_err, max_err):
    plot_name = 'Hermite, węzły równoodległe, n=' + repr(n)
    print(plot_name)
    x_inter, x_print, y_inter, y_print, p_print = interpolate_hermite(a, b, n)
    eukl_norm, max_norm = calculate_errors(y_print, p_print)
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm
    print_errors(eukl_norm, max_norm)
    print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name)


def exercise_hermite_ch(a, b, n, eukl_err, max_err):
    plot_name = 'Hermite, węzły Czebyszewa, n=' + repr(n)
    print(plot_name)
    x_inter, x_print, y_inter, y_print, p_print = interpolate_hermite_ch(a, b, n)
    eukl_norm, max_norm = calculate_errors(y_print, p_print)
    eukl_err[n] = eukl_norm
    max_err[n] = max_norm
    print_errors(eukl_norm, max_norm)
    print_plots(x_inter, x_print, y_inter, y_print, p_print, plot_name)


def exercise_2():
    a = -np.pi
    b = 2 * np.pi

    eukl_errors = {}
    max_errors = {}
    for i in range(2, 11):
        exercise_hermite(a, b, i, eukl_errors, max_errors)
    for i in range(15, 31, 5):
        exercise_hermite(a, b, i, eukl_errors, max_errors)
    hermite_errors = {'Eukl': eukl_errors, 'Max': max_errors}

    eukl_errors = {}
    max_errors = {}
    for i in range(2, 11):
        exercise_hermite_ch(a, b, i, eukl_errors, max_errors)
    for i in range(15, 31, 5):
        exercise_hermite_ch(a, b, i, eukl_errors, max_errors)
    hermite_ch_errors = {'Eukl': eukl_errors, 'Max': max_errors}

    return hermite_errors, hermite_ch_errors


exercise_2()
