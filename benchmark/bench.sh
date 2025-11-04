
#!/usr/bin/env bash
set -e
mkdir -p ../data
EXE=../build/bench
OUT=../data/results.csv

echo "impl,N,threads,run,sec" > "$OUT"

sizes=(128 256 512 1024)
impls=(naive reorder omp tiled simd)
threads=(1 2 4 8)

for N in "${sizes[@]}"; do
  for impl in "${impls[@]}"; do
    for t in "${threads[@]}"; do
      echo "Running $impl N=$N threads=$t"
      $EXE --impl "$impl" --N "$N" --threads "$t" --reps 3 >> "$OUT"
    done
  done
done

echo "Results saved to $OUT"

