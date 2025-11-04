
# naive_matmul.py
"""
Naive Python implementation of matrix multiplication (no NumPy dot).
Triple nested loops, O(N^3) time.
"""

def matmul_naive(A, B, N):
    """Compute C = A x B for NxN matrices represented as lists of lists."""
    C = [[0.0 for _ in range(N)] for _ in range(N)]
    for i in range(N):
        for j in range(N):
            s = 0.0
            for k in range(N):
                s += A[i][k] * B[k][j]
            C[i][j] = s
    return C


def gen_matrix(N):
    """Generate a deterministic NxN matrix."""
    return [[float((i + j) % 100) / 100.0 for j in range(N)] for i in range(N)]


if __name__ == "__main__":
    import time, sys
    N = int(sys.argv[1]) if len(sys.argv) > 1 else 128
    A = gen_matrix(N)
    B = gen_matrix(N)
    t0 = time.perf_counter()
    matmul_naive(A, B, N)
    t1 = time.perf_counter()
    print(f"Naive Python: N={N} time={t1-t0:.6f}s")

