#!/bin/bash
#SBATCH --job-name=part2_v2
#SBATCH --output=part2_v2.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 10:00:00

./part2_v2
