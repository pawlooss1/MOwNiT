import pandas as pd
import matplotlib.pyplot as plt
from ex1 import exercise_1

# from ex2 import exercise_2

plt.close('all')
data = {}


def read_data():
    polynomial_errors = exercise_1()
    # cubic = exercise_2()
    polynomial_data = {}
    outside = [] #list(polynomial_errors.keys())
    for key in polynomial_errors[2]['Eukl'].keys():
        outside += list(polynomial_errors.keys())
    inside = []
    for key in polynomial_errors.keys():
        inside += polynomial_errors[key]['Eukl'].keys()
    hier_index = list(zip(outside, inside))
    hier_index = pd.MultiIndex.from_tuples(hier_index)
    print(outside, inside)
    print(list(zip(outside, inside)))
    print(hier_index)
    for key in polynomial_errors.keys():
        polynomial_data[key] = pd.DataFrame(polynomial_errors[key])
    data['Polynomial'] = pd.DataFrame(polynomial_data, index=hier_index)
    # data['Cubic'] = pd.DataFrame(cubic)


def write_excel():
    writer = pd.ExcelWriter('Errors.xlsx')
    for (name, df) in data.items():
        df.to_excel(writer, name)
    writer.save()


def plot_errors(method):
    df = data[method]
    x = df.index.values
    eukl = df['Eukl'].values
    max = df['Max'].values
    fig, axes = plt.subplots(1, 2, figsize=(10, 4))
    fig.suptitle(method)
    axes[0].plot(x, eukl, '.')
    axes[1].plot(x, max, '.')
    for i in range(2):
        axes[i].set_title('Norma ' + repr(i + 1))
        axes[i].set_xlabel('n')
        axes[i].set_ylabel('norm(W(x)-f(x))')
    plt.show()


def do_all():
    read_data()
    write_excel()
    plot_errors()
