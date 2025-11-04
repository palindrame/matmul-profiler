
#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static inline double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

static inline float *alloc_f32(size_t n) {
    void *p = NULL;
    posix_memalign(&p, 64, n * sizeof(float));
    memset(p, 0, n * sizeof(float));
    return (float *)p;
}

static inline void init_mats(int N, float *A, float *B) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i * N + j] = (float)((i + j) % 100) / 100.0f;
            B[i * N + j] = (float)((i - j) % 100) / 100.0f;
        }
}

