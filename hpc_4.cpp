%%writefile cuda_program.cu

#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// =====================================================
// VECTOR ADDITION KERNEL
// =====================================================

__global__ void vectorAddition(int *a, int *b, int *c)
{
    int i = threadIdx.x;

    c[i] = a[i] + b[i];
}

// =====================================================
// MATRIX MULTIPLICATION KERNEL
// =====================================================

#define N 2

__global__ void matrixMultiplication(int a[N][N],
                                     int b[N][N],
                                     int c[N][N])
{
    int row = threadIdx.y;
    int col = threadIdx.x;

    c[row][col] = 0;

    for (int k = 0; k < N; k++)
    {
        c[row][col] +=
        a[row][k] * b[k][col];
    }
}

// =====================================================
// MAIN FUNCTION
// =====================================================

int main()
{
    // =================================================
    // VECTOR ADDITION
    // =================================================

    int n = 5;

    int a[] = {1, 2, 3, 4, 5};
    int b[] = {5, 4, 3, 2, 1};

    int c[5];

    int *d_a, *d_b, *d_c;

    // Allocate GPU memory

    cudaMalloc((void**)&d_a, n * sizeof(int));
    cudaMalloc((void**)&d_b, n * sizeof(int));
    cudaMalloc((void**)&d_c, n * sizeof(int));

    // Copy data from CPU to GPU

    cudaMemcpy(d_a, a,
               n * sizeof(int),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_b, b,
               n * sizeof(int),
               cudaMemcpyHostToDevice);

    // Launch vector addition kernel

    vectorAddition<<<1, n>>>(d_a, d_b, d_c);

    // Copy result from GPU to CPU

    cudaMemcpy(c, d_c,
               n * sizeof(int),
               cudaMemcpyDeviceToHost);

    cout << "Vector Addition Result:\n";

    for (int i = 0; i < n; i++)
    {
        cout << c[i] << " ";
    }

    cout << endl << endl;

    // Free vector memory

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // =================================================
    // MATRIX MULTIPLICATION
    // =================================================

    int matA[N][N] = {
        {1, 2},
        {3, 4}
    };

    int matB[N][N] = {
        {5, 6},
        {7, 8}
    };

    int matC[N][N];

    int (*d_matA)[N];
    int (*d_matB)[N];
    int (*d_matC)[N];

    // Allocate GPU memory

    cudaMalloc((void**)&d_matA, sizeof(matA));
    cudaMalloc((void**)&d_matB, sizeof(matB));
    cudaMalloc((void**)&d_matC, sizeof(matC));

    // Copy matrices from CPU to GPU

    cudaMemcpy(d_matA, matA,
               sizeof(matA),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_matB, matB,
               sizeof(matB),
               cudaMemcpyHostToDevice);

    // Configure threads

    dim3 threads(N, N);

    // Launch matrix multiplication kernel

    matrixMultiplication<<<1, threads>>>
    (d_matA, d_matB, d_matC);

    // Copy result back to CPU

    cudaMemcpy(matC, d_matC,
               sizeof(matC),
               cudaMemcpyDeviceToHost);

    cout << "Matrix Multiplication Result:\n";

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matC[i][j] << " ";
        }

        cout << endl;
    }

    // Free matrix memory

    cudaFree(d_matA);
    cudaFree(d_matB);
    cudaFree(d_matC);

    return 0;
}