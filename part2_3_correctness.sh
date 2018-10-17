#!/bin/bash
#SBATCH --job-name=part2_3_correctness
#SBATCH --output=part2_3_correctness.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 05:00:00

./part2_3_correctness

