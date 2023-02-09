#create 2 random dice
import random
import math
import matplotlib.pyplot as plt
import numpy as np

Nbase = 100000
Nexp = 500000
faces = 20

Na, Nb = faces, faces
Ma, Mb = faces, faces
M = (Ma + Mb)/2

Nab = []

def Ab(dadoA, dadoB):
    count = 0
    for i in range(Na):
        for j in range(Nb):
            if dadoA[i] > dadoB[j]:
                count += 1
    return count

for i in range(Nexp):
    dadoA = [random.randint(1,Ma) for i in range(Na)]
    dadoB = [random.randint(1,Mb) for i in range(Nb)]

    Nab.append(Ab(dadoA, dadoB))

soma = sum(Nab)
media = soma / len(Nab)
var = math.sqrt(sum([(i - media)**2 for i in Nab]) / (len(Nab) - 1))

mediaAlg = Na*Nb*(M - 1)/(2*M)
varAlg = math.sqrt(Na*Nb*(M**2 - 1)*(Na + Na + 1)/(12*M**2))

print(f'for {faces} faces, media={media} -> media algebrica={mediaAlg} e var={var} -> var algebrica = {varAlg}.')

normalizada = [(i-media)/var for i in Nab]
normalizadaAlg = [(i-mediaAlg)/math.sqrt(varAlg) for i in Nab]

# create a histogram

bins = 30

fig, ax = plt.subplots()
plt.hist(normalizada, bins=bins, density=True, color='blue')
# plt.hist(normalizadaAlg, bins=bins, density=True, color='red', histtype='step')

# plot a normal distribution normalizada
x = np.linspace(-10, 10, 200)
p = np.exp(-x**2/2)/math.sqrt(2*math.pi)
plt.plot(x, p, 'k', linewidth=2)


plt.show()
