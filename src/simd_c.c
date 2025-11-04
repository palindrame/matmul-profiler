
#include <immintrin.h>
#include "matmul_common.h"

void matmul_simd(int N, const float *A, const float *B, float *C) {
    const int V = 8; // AVX2
    for (int i = 0; i < N; ++i)
        for (int k = 0; k < N; ++k) {
            __m256 a_vec = _mm256_set1_ps(A[i * N + k]);
            int j = 0;
            for (; j + V <= N; j += V) {
                __m256 b_vec = _mm256_loadu_ps(&B[k * N + j]);
                __m256 c_vec = _mm256_loadu_ps(&C[i * N + j]);
                c_vec = _mm256_fmadd_ps(a_vec, b_vec, c_vec);
                _mm256_storeu_ps(&C[i * N + j], c_vec);
            }
            for (; j < N; ++j)
                C[i * N + j] += A[i * N + k] * B[k * N + j];
        }
}

