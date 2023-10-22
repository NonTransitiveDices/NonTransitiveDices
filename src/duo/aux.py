from more_itertools import distinct_permutations
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

    total = 9
    values = 9
    victory1 = 0

    for i in range(values):
        victory1 += die1[i] * sum(die2[i+1:])

    if victory1 > total/2:
        return 1
        
    else:

        victory2 = 0

        for i in range(values):
            victory2 += die2[i] * sum(die1[i+1:])

        if victory1 > victory2:
            return 1

        else:
            return 0


for i in range(3, 16):

    dices, faces, values = 3, i, 4

    with open(f'data/dados{i}.txt', 'w') as file:

        print("feito", i)

        permutations = permutate(values, faces)

        count = 0
        text = ''

        for permutation in permutations:
            if 0 in permutation:
                continue
            else:
                count += 1
                text_aux = ' '.join(str(x) for x in permutation)
                text_aux += '\n'
                text += text_aux

        file.write(str(dices) + '\n')
        file.write(str(faces) + '\n')
        file.write(str(values) + '\n')
        file.write(str(count) + '\n')
        file.write(text)

# with open('compare.txt', 'r') as file:
#     text = file.read()
#     text = text.split('\n')

#     lista = []
#     count = 0
#     for line in text:
#         line = line.split('-')
#         lista_aux = []
#         for l in line:
#             l = l.split(' ')
#             l = [int(x) for x in l if x != '']
#             lista_aux.append(l)
#         lista.append(lista_aux)
#         count += 1

#     for bloco in lista:
#         result = abTransitive(bloco[0], bloco[1])
#         if result == bloco[2][0]:
#             continue
#         else:
# #             print('not ok')
# #             print(bloco[0], bloco[1], result)
# #             print(bloco[0], bloco[1], bloco[2])

# with open('data/result/result.txt', 'r') as file:
#     text = file.read()
#     text = text.split('\n')
#     lista = []
#     for line in text:
#         lista_aux = []
#         line = line.split(' ')
#         # print([line[7], line[9], line[12], line[16], line[18]])
#         lista_aux.append([int(line[7]), int(line[9]), int(line[12]), line[16], float(line[18])])
#         lista.append(lista_aux)

#     for bloco in lista:
#         print(bloco[0])
#         plt.plot(bloco[0][1], bloco[0][-1], 'ro')

#     plt.xlabel('Pesos/Faces disponíveis')
#     plt.ylabel('Probability')
#     plt.title(f'Probability of 3 non transitive dice with 4 values')
#     plt.grid(True)
#     plt.show()
#     plt.show()
