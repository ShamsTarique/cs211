#!/bin/bash
#SBATCH --job-name=p2_b128
#SBATCH --output=p2_b128.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 05:10:00

./p2_b128
