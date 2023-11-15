#!/bin/bash

set -x 

srun -N 2 -n 2 ./mpi_sync 10 16384 0 
srun -N 2 -n 2 ./mpi_sync 10 32768 0 
srun -N 2 -n 2 ./mpi_sync 10 65536 0 
srun -N 2 -n 2 ./mpi_sync 10 131072 0 
srun -N 2 -n 2 ./mpi_sync 10 262144 0 
srun -N 2 -n 2 ./mpi_sync 10 524288 0 
srun -N 2 -n 2 ./mpi_sync 10 1048576 0 
srun -N 2 -n 2 ./mpi_sync 10 2097152 0 
srun -N 2 -n 2 ./mpi_sync 10 4194304 0 
srun -N 2 -n 2 ./mpi_sync 10 8388608 0 
srun -N 2 -n 2 ./mpi_sync 10 16777216 0 
srun -N 2 -n 2 ./mpi_sync 10 33554432 0 
