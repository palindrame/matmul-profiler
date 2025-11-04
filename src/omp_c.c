
#include <omp.h>
#include "matmul_common.h"

void matmul_omp(int N, const float *A, const float *B, float *C, int threads) {
    omp_set_num_threads(threads);
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i)
        for (int k = 0; k < N; ++k) {
            float a = A[i * N + k];
            const float *Brow = &B[k * N];
            float *Crow = &C[i * N];
            for (int j = 0; j < N; ++j)
                Crow[j] += a * Brow[j];
        }
}

