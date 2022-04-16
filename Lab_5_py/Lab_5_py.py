# -*- coding: cp1251 -*-
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
import numpy as np
import csv

mas = [[],[]]
x = []
y = []
size = 0
with open('../example.csv', 'r') as f:
    content = csv.reader(f, delimiter= ';')
    counter = 0
    for row in content:
        if (counter == 0):
            size = int(row[0])
        if (counter < size+1 and counter > 0):
            mas[0].append(float(row[0]))
            mas[1].append(float(row[1]))
        elif (counter > 0):
            x.append(float(row[0]))
            y.append(float(row[1]))
        print(row);
        counter += 1
        
        






#for i in range (2):
#    size = len(mas[i])
#    for j in range(size - 1):
#        if (i == 0):
#            x.append(float(mas[i][j]))
#        if (i == 1):
#            y.append(float(mas[i][j]))



#print(type(x[2]))
fig, ax = plt.subplots(figsize=(8, 6))


ax.set_title("линейная зависимость y = x")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.grid(which="major", linewidth=1.2)
ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)

ax.plot(x, y, "-r", label="y = 2^x")    
ax.plot(mas[0], mas[1], "h-b", linestyle="--")

x1 = x[0]
x2 = x[len(x) - 1] 
y1 = y[0]
y2 = y[len(y) - 1] 


ax.set_ylim([y1, y2])
ax.set_xlim([x1, x2])
#plt.stem(x, y, linefmt="r--")
ax.legend()


ax.xaxis.set_minor_locator(AutoMinorLocator())
ax.yaxis.set_minor_locator(AutoMinorLocator())
ax.tick_params(which='major', length=10, width=2)
ax.tick_params(which='minor', length=5, width=1)

plt.show()
