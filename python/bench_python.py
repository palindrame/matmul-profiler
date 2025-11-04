
#!/usr/bin/env python3
"""
Benchmark harness for naive Python matrix multiplication.
Appends results to ../data/results.csv
"""

import time
import os
import csv
from naive_matmul import matmul_naive, gen_matrix

def run_bench(N, reps=3):
    """Run the naive Python matmul N x N several times."""
    A = gen_matrix(N)
    B = gen_matrix(N)
    times = []
    for r in range(reps):
        t0 = time.perf_counter()
        matmul_naive(A, B, N)
        t1 = time.perf_counter()
        times.append(t1 - t0)
    return sum(times) / len(times)

def main():
    sizes = [32, 64, 128, 256]
    os.makedirs("../data", exist_ok=True)
    out_path = "../data/results.csv"
    header = ["impl","N","threads","run","sec"]

    # append to same CSV as C benchmarks
    new_file = not os.path.exists(out_path)
    with open(out_path, "a", newline="") as f:
        writer = csv.writer(f)
        if new_file:
            writer.writerow(header)
        for N in sizes:
            sec = run_bench(N)
            print(f"Python naive N={N} avg={sec:.6f}s")
            writer.writerow(["python_naive", N, 1, 0, f"{sec:.6f}"])

if __name__ == "__main__":
    main()

