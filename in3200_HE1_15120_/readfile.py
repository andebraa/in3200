import numpy as np
import matplotlib.pyplot as plt

cml1 = np.zeros(9)
cml2 = np.zeros(9)
def readfile(filename):
    infile = open(filename, 'r')
    for i,line in enumerate(infile):
        elem = line.split()
        cml1[i] = float(elem[0].strip())
        cml2[i] = float(elem[1].strip())

    return cml1, cml2

cml1, cml2 = readfile('time_data_notredame.txt')

threads = []

i = 1
while i < 512:
    threads.append(i)
    i *= 2
plt.plot(threads, cml2, label="cml2")
#plt.plot(threads, cml1, label ="cml1")
plt.xlabel("number of threads")
plt.ylabel("time [s]")
plt.title("time spent using web-NotreDame")
plt.legend()
plt.show()
