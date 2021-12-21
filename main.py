import random as rand
import numpy as np

A = []
B = []


for i in range(1000):
    A.append([])
    A[i].append(rand.randint(-100,100))
    A[i].append(A[i][0])
    for j in range(45):
        A[i].append(rand.randint(-20, 20))
    
    A[i].append(rand.randint(-100,100))
    A[i].append(-2 * A[i][47])
    
    A[i].append(rand.randint(-100,100))
    A[i].append(A[i][49])

    A[i].append(rand.randint(-100,100))
    A[i].append(A[i][51])

    for j in range(45):
        A[i].append(rand.randint(-5, 5))

    A[i].append(rand.randint(-100,100))
    A[i].append(A[i][98])

#print(A)

for i in range(100):
    B.append([])
    B[i].append(rand.randint(-100,100))
    B[i].append(B[i][0])
    for j in range(45):
        B[i].append(rand.randint(-20, 20))
    
    B[i].append(rand.randint(-100,100))
    B[i].append(-2 * B[i][47])
    
    B[i].append(rand.randint(-100,100))
    B[i].append(B[i][49])

    B[i].append(rand.randint(-100,100))
    B[i].append(B[i][51])

    for j in range(45):
        B[i].append(rand.randint(-5, 5))

    B[i].append(rand.randint(-100,100))
    B[i].append(B[i][98])

R = np.matmul(np.transpose(A), A)

rank = np.linalg.matrix_rank(R)
print(f"rank: {rank}")

U, S, VT = np.linalg.svd(R)


data = {}

for i in range(9, rank, 5):
    avg = 0.0
    for j in range(100): # for 100 vectors
        hatX = np.zeros(100)
        for k in range(i+1): 
            c = np.inner(U[k],B[j])
            hatX += np.multiply(U[k], c)
        
        distance = np.linalg.norm(B[j] - hatX)
        #print(distance)
        avg += distance
    data[i] = avg / 100

for key in data.keys():
    print(f"{int(key)+1} {data[key]}")
