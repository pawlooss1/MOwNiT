import pandas as pd
import matplotlib.pyplot as plt
from ex1 import exercise_1
from ex2 import exercise_2

plt.close('all')
data = {}


def read_data():
    lagrange, newton, lagrange_ch, newton_ch = exercise_1()
    hermite, hermite_ch = exercise_2()
    data['Lagrange'] = pd.DataFrame(lagrange)
    data['Lagrange_ch'] = pd.DataFrame(lagrange_ch)
    data['Newton'] = pd.DataFrame(newton)
    data['Newton_ch'] = pd.DataFrame(newton_ch)
    data['Hermite'] = pd.DataFrame(hermite)
    data['Hermite_ch'] = pd.DataFrame(hermite_ch)


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
        axes[i].set_title('Norma ' + repr(i+1))
        axes[i].set_xlabel('n')
        axes[i].set_ylabel('norm(W(x)-f(x))')
    plt.show()
