#!/bin/bash
#SBATCH --job-name=p2_b32
#SBATCH --output=p2_b32.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 05:00:00

./p2_b32
