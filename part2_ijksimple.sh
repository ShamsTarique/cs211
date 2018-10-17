#!/bin/bash
#SBATCH --job-name=part2_ijksimple
#SBATCH --output=part2_ijksimple.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 03:00:00

./part2_ijksimple

