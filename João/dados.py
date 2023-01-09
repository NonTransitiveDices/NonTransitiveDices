# we gonna search for non transitive dice

import random
from more_itertools import distinct_permutations
from collections import namedtuple
import matplotlib.pyplot as plt


def permutate(values, faces):
    
    topermutate = [1 for _ in range(faces)] + [0 for _ in range(values-1)]
    topermutate = ''.join(str(x) for x in topermutate)

    permutations = distinct_permutations(topermutate)

    aux = []

    for permutation in permutations:
        permutation = ''.join(permutation).split('0')
        permutation = [len(x) for x in permutation]
        aux.append(permutation)

    return aux.copy()

def abTransitive(die1, die2):

    total = faces * faces
    victory1 = 0

    for i in range(values):
        victory1 += die1[i] * sum(die2[i+1:])

    if victory1 > total/2:
        return True
        
    else:

        victory2 = 0

        for i in range(values):
            victory2 += die2[i] * sum(die1[i+1:])

        if victory1 > victory2:
            return True

        else:
            return False

def recursiveTransitive(matrix, die = 0):

    count = 0

    if die == dices:

        if abTransitive(matrix[-1], matrix[0]):
            return 1
        else:
            return 0
        
    else:

        for permutation in permutations:

            if die == 0:

                matrix[die] = permutation
                count += recursiveTransitive(matrix=matrix, die=die+1)

            else:

                if abTransitive(matrix[die-1], permutation):

                    matrix[die] = permutation
                    count += recursiveTransitive(matrix=matrix, die=die+1)

    return count


# create enum for configurações
config = namedtuple('Config', ['values', 'faces', 'dices'])

for valor in range(9, 10):

    C = config(values=valor,faces=3, dices=3)

    permutations = permutate(C.values, C.faces)

    matriz = [[0 for x in range(C.values)] for y in range(C.dices)]

    values = C.values
    faces = C.faces
    dices = C.dices

    Qtd_dados = recursiveTransitive(matrix=matriz)    

    total = len(permutations)**C.dices

    print(f'For {C.values} values, {C.faces} faces and {C.dices} dices : {Qtd_dados},{total}')
    print(f'For {C.values} values, {C.faces} faces and {C.dices} dices, the probability is {Qtd_dados/total}')

    plt.plot(C.values, Qtd_dados/total, 'ro')

plt.xlabel('n')
plt.ylabel('Probability')
plt.suptitle('Probability of 3 non transitive dice')
plt.title('For n,n faces/values')
plt.grid(True)
plt.show()


