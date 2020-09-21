from sklearn.ensemble import IsolationForest

import csv

with open("sheet1.csv") as csvfile:
    reader = csv.reader(csvfile, quotechar='\"', dialect='excel')
    next(reader)
    for row in reader:
        point = row[1]
        print(float(point))
