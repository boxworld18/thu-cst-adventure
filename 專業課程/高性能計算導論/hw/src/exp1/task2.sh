#!/bin/bash

set -x

srun -N 2 -n 2 ./mpi_sync 10 100000000 10
srun -N 2 -n 2 ./mpi_async 10 100000000 10

srun -N 2 -n 2 ./mpi_sync 10 100000000 20
srun -N 2 -n 2 ./mpi_async 10 100000000 20

srun -N 2 -n 2 ./mpi_sync 10 100000000 40
srun -N 2 -n 2 ./mpi_async 10 100000000 40

srun -N 2 -n 2 ./mpi_sync 10 100000000 80
srun -N 2 -n 2 ./mpi_async 10 100000000 80

srun -N 2 -n 2 ./mpi_sync 10 100000000 160
srun -N 2 -n 2 ./mpi_async 10 100000000 160
