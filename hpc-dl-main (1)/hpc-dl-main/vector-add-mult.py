from numba import cuda
import numpy as np


# Vector Addition
@cuda.jit
def vector_add(a, b, c):

    i = cuda.threadIdx.x

    if i < len(c):

        c[i] = a[i] + b[i]


# Matrix Multiplication
@cuda.jit
def vector_multi(a, b, c):

    row, col = cuda.grid(2)

    if row < c.shape[0] and col < c.shape[1]:

        c[row][col] = 0

        for k in range(a.shape[1]):

            c[row][col] += a[row][k] * b[k][col]


# -------- VECTOR INPUT --------

a = np.array(
    list(map(int,
    input("Enter first vector: ").split()))
)

b = np.array(
    list(map(int,
    input("Enter second vector: ").split()))
)

c = np.zeros(len(a))

vector_add[1, len(a)](a, b, c)

print("Vector Addition:")

print(c)


# -------- MATRIX INPUT --------

print("Enter first 2x2 matrix:")

a = np.array([
    list(map(int, input().split())),
    list(map(int, input().split()))
])

print("Enter second 2x2 matrix:")

b = np.array([
    list(map(int, input().split())),
    list(map(int, input().split()))
])

c = np.zeros((2,2))

vector_multi[(1,1),(2,2)](a, b, c)

print("Matrix Multiplication:")

print(c)