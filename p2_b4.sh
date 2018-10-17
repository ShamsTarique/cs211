#!/bin/bash
#SBATCH --job-name=p2_b4
#SBATCH --output=p2_b4.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 05:10:00

./p2_b4
