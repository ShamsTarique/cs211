#!/bin/bash
#SBATCH --job-name=part2_4
#SBATCH --output=part2_4_o3_2.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 05:00:00

./part2_4
