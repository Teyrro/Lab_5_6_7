
import matplotlib.pyplot as plt
import csv

mas = [[],[]]

with open('../example.csv', 'r') as f:
    content = csv.reader(f, delimiter=';')
    count = 0
    for row in content:
        size = len(row)
        for i in range (size):
            mas[count].append(row[i])
        count += 1

x = []
y = []
for row in mas:
    print(row)

for i in range (2):
    size = len(mas[i])
    for j in range(size - 1):
        if (i == 0):
            x.append(float(mas[i][j]))
        if (i == 1):
            y.append(float(mas[i][j]))


print(type(x[2]))

plt.plot(x, y)
plt.show()
