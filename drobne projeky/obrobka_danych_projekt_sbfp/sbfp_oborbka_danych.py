import pandas as pd
import os
import math
import numpy as np
import fileinput
os.getcwd()


with fileinput.FileInput("dane_c_calosc.csv", inplace=True) as file:
    for line in file:
        print(line.replace(",", "."), end='')

dane = pd.read_csv('dane_c_calosc.csv', delimiter='\t')


dane['tbf'] = dane['tbf'].astype(float)
dane['ttr'] = dane['ttr'].astype(float)


length = len(dane)
min_tbf = dane['tbf'].min()
max_tbf = dane['tbf'].max()
range_tbf=max_tbf-min_tbf

sqrt_length = math.sqrt(length)
liczba_klas = round(sqrt_length)

min_ttr = dane['ttr'].min()
max_ttr = dane['ttr'].max()
range_ttr=max_ttr-min_ttr

dx_tbf = range_tbf/liczba_klas
dx_ttr = range_ttr/liczba_klas

przedzialy_tbf=[]
przedzialy_tbf.append(min_tbf)
przedzialy_ttr=[]
przedzialy_ttr.append(min_ttr)


for i in range(liczba_klas):
    ole1 = przedzialy_tbf[i]
    ole1 = ole1 + dx_tbf
    przedzialy_tbf.append(ole1)

for i in range(liczba_klas):
    ole2 = przedzialy_ttr[i]
    ole2 = ole2 + dx_ttr
    przedzialy_ttr.append(ole2)

zakresy_klas_tbf = np.zeros((liczba_klas, 2))
zakresy_klas_ttr = np.zeros((liczba_klas, 2))


for i in range(liczba_klas):
    for j in range(2):
        zakresy_klas_tbf[i][j]=przedzialy_tbf[i+j]
        zakresy_klas_ttr[i][j]=przedzialy_ttr[i+j]


licznosc_klas_tbf = [0] * liczba_klas
licznosc_klas_ttr = [0] * liczba_klas


dane_np = dane.to_numpy()

for i in range(liczba_klas):
    count_tbf = 0
    for j in range(len(dane_np)):
        if (dane_np[j][0] >= zakresy_klas_tbf[i][0] and dane_np[j][0] < zakresy_klas_tbf[i][1]):
            count_tbf = count_tbf + 1
        licznosc_klas_tbf[i]=count_tbf

ole_tbf=licznosc_klas_tbf[liczba_klas-1]
ole_tbf= ole_tbf+1
licznosc_klas_tbf[liczba_klas-1]=ole_tbf


for i in range(liczba_klas):
    count_ttr = 0
    for j in range(len(dane_np)):
        if (dane_np[j][1] >=  zakresy_klas_ttr[i][0] and dane_np[j][1] <  zakresy_klas_ttr[i][1]):
            count_ttr = count_ttr + 1
        licznosc_klas_ttr[i]=count_ttr


ole_ttr=licznosc_klas_ttr[liczba_klas-1]
ole_ttr= ole_ttr+1
licznosc_klas_ttr[liczba_klas-1]=ole_ttr


licznosc_klas_tbf_np=np.array(licznosc_klas_tbf)
licznosc_klas_ttr_np=np.array(licznosc_klas_ttr)
licznosc_klas=np.vstack((licznosc_klas_tbf_np, licznosc_klas_ttr_np)).T



srednie_kolumn = dane_np.mean(axis=0)
mtbf = srednie_kolumn[0]
mttr = srednie_kolumn[1]
lambda1 = 1/mtbf
mi1 = 1/mttr
gotowosc = mi1/(lambda1+mi1)



text_file = open("wartosci_z_danych.txt", "w")
text_file.write("dlugosc: %s \n" % length)
text_file.write("rozstep_tbf: %s \n" % range_tbf)
text_file.write("liczba_klas: %s \n" % liczba_klas)
text_file.write("\n")
text_file.write("rozstep_ttr: %s \n" % range_ttr)
text_file.write("\n")
text_file.write("mtbf: %s \n" % mtbf)
text_file.write("mttr: %s \n" % mttr)
text_file.write("lambda: %s \n" % lambda1)
text_file.write("mi: %s \n" % mi1)
text_file.write("gotowoscP: %s \n" % gotowosc)
text_file.close()


np.savetxt("z_licznosc_klas.csv", licznosc_klas , delimiter='; ')

np.savetxt("zakresy_klas_tbf.csv", zakresy_klas_tbf, delimiter=';')
np.savetxt("zakresy_klas_ttr.csv", zakresy_klas_ttr, delimiter=';')


with fileinput.FileInput("wartosci_z_danych.txt", inplace=True) as file:
    for line in file:
        print(line.replace(".", ","), end='')

with fileinput.FileInput("z_licznosc_klas.csv", inplace=True) as file:
    for line in file:
        print(line.replace(".", ","), end='')

with fileinput.FileInput("zakresy_klas_tbf.csv", inplace=True) as file:
    for line in file:
        print(line.replace(".", ","), end='')

with fileinput.FileInput("zakresy_klas_ttr.csv", inplace=True) as file:
    for line in file:
        print(line.replace(".", ","), end='')
