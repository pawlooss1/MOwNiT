import pandas as pd
from ex1 import exercise

lagrange, newton, lagrange_ch, newton_ch = exercise()
writer = pd.ExcelWriter('Errors.xlsx')
lagrange.to_excel(writer, 'Lagrange')
newton.to_excel(writer, 'Newton')
lagrange_ch.to_excel(writer, 'Lagrange_ch')
newton_ch.to_excel(writer, 'Newton_ch')
writer.save()
