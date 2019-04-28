import pandas as pd
from ex1 import exercise_1
from ex2 import exercise_2

lagrange, newton, lagrange_ch, newton_ch = exercise_1()
hermite, hermite_ch = exercise_2()

lagrange = pd.DataFrame(lagrange)
lagrange_ch = pd.DataFrame(lagrange_ch)
newton = pd.DataFrame(newton)
newton_ch = pd.DataFrame(newton_ch)
hermite = pd.DataFrame(hermite)
hermite_ch = pd.DataFrame(hermite_ch)

writer = pd.ExcelWriter('Errors.xlsx')
lagrange.to_excel(writer, 'Lagrange')
newton.to_excel(writer, 'Newton')
lagrange_ch.to_excel(writer, 'Lagrange_ch')
newton_ch.to_excel(writer, 'Newton_ch')
hermite.to_excel(writer, 'Hermite')
hermite_ch.to_excel(writer, 'Hermite_ch')

writer.save()
