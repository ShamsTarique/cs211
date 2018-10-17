#!/bin/bash
#SBATCH --job-name=part1_v3
#SBATCH --output=part1_v3_2.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 05:00:00

./part1_v3
