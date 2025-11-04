
#include "matmul_common.h"
#include <string.h>
#include <omp.h>

void matmul_naive(int, const float*, const float*, float*);
void matmul_reorder(int, const float*, const float*, float*);
void matmul_omp(int, const float*, const float*, float*, int);
void matmul_tiled(int, const float*, const float*, float*);
void matmul_simd(int, const float*, const float*, float*);

int main(int argc, char **argv) {
    const char *impl = "naive";
    int N = 512, reps = 3, threads = 4;

    for (int i=1;i<argc;i++){
        if(!strcmp(argv[i],"--impl")) impl = argv[++i];
        else if(!strcmp(argv[i],"--N")) N = atoi(argv[++i]);
        else if(!strcmp(argv[i],"--reps")) reps = atoi(argv[++i]);
        else if(!strcmp(argv[i],"--threads")) threads = atoi(argv[++i]);
    }

    float *A = alloc_f32((size_t)N*N);
    float *B = alloc_f32((size_t)N*N);
    float *C = alloc_f32((size_t)N*N);
    init_mats(N, A, B);

    for (int r = 0; r < reps; ++r) {
        memset(C, 0, sizeof(float)*N*N);
        double t0 = now_seconds();

        if (!strcmp(impl,"naive")) matmul_naive(N,A,B,C);
        else if (!strcmp(impl,"reorder")) matmul_reorder(N,A,B,C);
        else if (!strcmp(impl,"omp")) matmul_omp(N,A,B,C,threads);
        else if (!strcmp(impl,"tiled")) matmul_tiled(N,A,B,C);
        else if (!strcmp(impl,"simd")) matmul_simd(N,A,B,C);
        else { fprintf(stderr,"Unknown impl %s\n",impl); return 1; }

        double t1 = now_seconds();
        printf("%s,%d,%d,%d,%.6f\n", impl, N, threads, r, t1-t0);
        fflush(stdout);
    }

    free(A); free(B); free(C);
    return 0;
}

