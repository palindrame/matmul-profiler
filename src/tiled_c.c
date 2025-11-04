
#include "matmul_common.h"
#define TILE 64

void matmul_tiled(int N, const float *A, const float *B, float *C) {
    for (int ii = 0; ii < N; ii += TILE)
        for (int kk = 0; kk < N; kk += TILE)
            for (int jj = 0; jj < N; jj += TILE) {
                int i_max = (ii + TILE < N) ? ii + TILE : N;
                int k_max = (kk + TILE < N) ? kk + TILE : N;
                int j_max = (jj + TILE < N) ? jj + TILE : N;
                for (int i = ii; i < i_max; ++i)
                    for (int k = kk; k < k_max; ++k) {
                        float a = A[i * N + k];
                        const float *Brow = &B[k * N];
                        float *Crow = &C[i * N];
                        for (int j = jj; j < j_max; ++j)
                            Crow[j] += a * Brow[j];
                    }
            }
}

