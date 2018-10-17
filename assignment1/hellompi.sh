#!/bin/bash
#SBATCH --job-name=hellompi
#SBATCH --output=res.txt
#SBATCH -N 2
#SBATCH -t 00:10:00

mpirun -np 64 ./hellompi 
