import os
import numpy as np
import pandas as pd

listFolder = ['./SERIALE-Simulation', './MPI-Simulation', './MPIv2-Simulation', './OMP-Simulation']
time = []

for folder in listFolder:
  listFile = os.listdir(folder)

  for element in listFile:
    print("File preso in esame: " + element)
    time.append(np.loadtxt(folder + '/' + element)[:, 2])

  break

print(time)
print(len(time[1]))

average = []
for i in range(0, len(time[0])):
  average.append(sum(row[i] for row in time) / 10)

print(average)