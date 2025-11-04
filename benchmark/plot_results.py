
#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys, os

sns.set(style="whitegrid")

def main(csv_file):
    df = pd.read_csv(csv_file)
    dfg = df.groupby(["impl","N","threads"])["sec"].median().reset_index()

    # Runtime vs N
    plt.figure(figsize=(8,5))
    sns.lineplot(data=dfg[dfg.threads==1], x="N", y="sec", hue="impl", marker="o")
    plt.title("Matrix Multiplication Runtime vs Matrix Size (1 thread)")
    plt.xlabel("Matrix size N")
    plt.ylabel("Seconds")
    plt.xscale("log"); plt.yscale("log")
    plt.tight_layout()
    plt.savefig("runtime_vs_N.png")
    print("Saved runtime_vs_N.png")

    # Speedup vs threads for each impl
    base = dfg[(dfg.impl=="omp") & (dfg.N==1024) & (dfg.threads==1)]["sec"].values[0]
    d1024 = dfg[dfg.N==1024]
    plt.figure(figsize=(8,5))
    sns.lineplot(data=d1024[d1024.impl=="omp"], x="threads", y="sec", marker="o")
    plt.title("OMP Implementation Scaling (N=1024)")
    plt.xlabel("Threads"); plt.ylabel("Seconds (lower is better)")
    plt.xscale("log"); plt.yscale("log")
    plt.tight_layout()
    plt.savefig("omp_scaling.png")
    print("Saved omp_scaling.png")

if __name__ == "__main__":
    if len(sys.argv)<2:
        print("Usage: plot_results.py data/results.csv")
        sys.exit(1)
    main(sys.argv[1])

