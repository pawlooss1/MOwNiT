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


def plot_lagrange():
    df = data['Lagrange']
    x = df.index.values
    eukl = df['Eukl'].values
    max = df['Max'].values
    plt.plot(x, eukl, '.')
    plt.plot(x, max, '.')
    plt.show()
