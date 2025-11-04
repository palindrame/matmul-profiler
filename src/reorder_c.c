
#include "matmul_common.h"

void matmul_reorder(int N, const float *A, const float *B, float *C) {
    for (int i = 0; i < N; ++i)
        for (int k = 0; k < N; ++k) {
            float a = A[i * N + k];
            const float *Brow = &B[k * N];
            float *Crow = &C[i * N];
            for (int j = 0; j < N; ++j)
                Crow[j] += a * Brow[j];
        }
}

