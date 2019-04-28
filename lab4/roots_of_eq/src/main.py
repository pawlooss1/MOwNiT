from functions import *


def f(x):
    return (x - 1) * np.exp(-10 * x) + x ** 15


def f_1(x):
    return np.exp(-10 * x) * (1 - 10 * (x - 1)) + 15 * x ** 14


X = np.linspace(-1, 0.7, 18)
ro = 0.0001
print('Newton:')
for x_start in X:
    print('x_pocz: %.1f' % x_start, 'ro: ', ro)
    result, n, fx = newton1(f, f_1, x_start, 1000, ro)
    print('wynik 1 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    result, n, fx = newton2(f, f_1, x_start, 1000, ro)
    print('wynik 2 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    print('')

X = np.linspace(-1, 0.7, 18)
ro = 0.000001
print('Newton:')
for x_start in X:
    print('x_pocz: %.1f' % x_start, 'ro: ', ro)
    result, n, fx = newton1(f, f_1, x_start, 1000, ro)
    print('wynik 1 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    result, n, fx = newton2(f, f_1, x_start, 1000, ro)
    print('wynik 2 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    print('')

X = np.linspace(-0.9, 0.6, 16)
ro = 0.0001
print('Sieczne:')
for x_start in X:
    print('Przedzial [-1, %.1f]' % x_start, 'ro: ', ro)
    result, n, fx = secant1(f, -1.0, x_start, 100, ro)
    print('wynik 1 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    result, n, fx = secant2(f, -1.0, 0.5, 100, ro)
    print('wynik 2 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    print('Przedzial [%.1f, 0.7]' % x_start, 'ro: ', ro)
    result, n, fx = secant1(f, 0.7, x_start, 100, ro)
    print('wynik 1 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    result, n, fx = secant2(f, 0.7, x_start, 100, ro)
    print('wynik 2 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    print('')

X = np.linspace(-0.9, 0.6, 16)
ro = 0.000001
print('Sieczne:')
for x_start in X:
    print('Przedzial [-1, %.1f]' % x_start, 'ro: ', ro)
    result, n, fx = secant1(f, -1.0, x_start, 100, ro)
    print('wynik 1 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    result, n, fx = secant2(f, -1.0, 0.5, 100, ro)
    print('wynik 2 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    print('Przedzial [%.1f, 0.7]' % x_start, 'ro: ', ro)
    result, n, fx = secant1(f, 0.7, x_start, 100, ro)
    print('wynik 1 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    result, n, fx = secant2(f, 0.7, x_start, 100, ro)
    print('wynik 2 kryterium: n =', n, ' x_0 =', result, ' f(x_0) =', fx)
    print('')

f1 = lambda x1, x2, x3: x1 ** 2 + x2 ** 2 - x3 ** 2 - 1
f2 = lambda x1, x2, x3: x1 - 2 * x2 ** 3 + 2 * x3 ** 2 + 1
f3 = lambda x1, x2, x3: 2 * x1 ** 2 + x2 - 2 * x3 ** 2 - 1
df1_dx1 = lambda x1, x2, x3: 2 * x1
df1_dx2 = lambda x1, x2, x3: 2 * x2
df1_dx3 = lambda x1, x2, x3: - 2 * x3
df2_dx1 = lambda x1, x2, x3: 1
df2_dx2 = lambda x1, x2, x3: - 6 * x2 ** 2
df2_dx3 = lambda x1, x2, x3: 2 * x3
df3_dx1 = lambda x1, x2, x3: 4 * x1
df3_dx2 = lambda x1, x2, x3: 1
df3_dx3 = lambda x1, x2, x3: - 4 * x3

F = np.array([[f1], [f2], [f3]])
J = np.array([[df1_dx1, df1_dx2, df1_dx3], [df2_dx1, df2_dx2, df2_dx3], [df3_dx1, df3_dx2, df3_dx3]])
X = np.array([[1], [1], [1]])

ro = 0.0001
print('Newton uklad:')
print('ro: ', ro)
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

X = np.array([[0.75], [0.75], [0.75]])
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

X = np.array([[2], [2], [2]])
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

X = np.array([[-1], [-1], [-1]])
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

ro = 0.000001
print('\n\nro: ', ro)
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

X = np.array([[0.75], [0.75], [0.75]])
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

X = np.array([[2], [2], [2]])
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)

X = np.array([[-1], [-1], [-1]])
print('\nwektor poczatkowy:\n', X)
result, n = newton_system1(F, J, X, ro)
print('wynik 1 kryterium: n =', n, ' X =\n', result)
result, n = newton_system2(F, J, X, ro)
print('wynik 2 kryterium: n =', n, ' X =\n', result)