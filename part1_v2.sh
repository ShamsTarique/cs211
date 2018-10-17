#!/bin/bash
#SBATCH --job-name=part1_v2
#SBATCH --output=part1_v2.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 40:00:00

./part1_v2
