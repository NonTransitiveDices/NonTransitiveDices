from more_itertools import distinct_permutations

def permutate(n):
    dado = 'A' * (n-1) + 'B' * n + 'C' * n
    permutations = distinct_permutations(dado)
    return permutations

def abcNtransitive(permutation, n):

    threshold = n**2/2
    countA, countB, countC = 0, 0, 0
    vicAB, vicBC, vicCA = 0, 0, 0

    for item in permutation:
        if item == 'A':
            countA += 1
            vicAB += countB
        elif item == 'B':
            countB += 1
            vicBC += countC
        elif item == 'C':
            countC += 1
            vicCA += countA
        
    if vicAB > threshold and vicBC > threshold and vicCA > threshold:
        return True
    elif vicAB < threshold and vicBC < threshold and vicCA < threshold:
        return True
    else:
        return False

n = 2
vec = permutate(n)
countCasos = 0
contTotal = 0
for item in vec:
    contTotal += 1
    # insert A in first position
    item = list(item)
    item.insert(0, 'A') 
    if abcNtransitive(item, n):
        countCasos += 1

print(f'casos não transitivos do total: {countCasos}/{contTotal} = {countCasos/contTotal}')