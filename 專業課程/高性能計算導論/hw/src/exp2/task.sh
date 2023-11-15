#!/bin/bash

set -x
srun -N 1 -n 1 ./allreduce 10 10000
srun -N 1 -n 1 ./allreduce 10 1000000
srun -N 1 -n 1 ./allreduce 10 100000000

srun -N 1 -n 7 ./allreduce 10 10000
srun -N 1 -n 7 ./allreduce 10 1000000
srun -N 1 -n 7 ./allreduce 10 100000000

srun -N 1 -n 14 ./allreduce 10 10000
srun -N 1 -n 14 ./allreduce 10 1000000
srun -N 1 -n 14 ./allreduce 10 100000000

srun -N 1 -n 28 ./allreduce 10 10000
srun -N 1 -n 28 ./allreduce 10 1000000
srun -N 1 -n 28 ./allreduce 10 100000000

srun -N 2 -n 2 ./allreduce 10 10000
srun -N 2 -n 2 ./allreduce 10 1000000
srun -N 2 -n 2 ./allreduce 10 100000000

srun -N 2 -n 14 ./allreduce 10 10000
srun -N 2 -n 14 ./allreduce 10 1000000
srun -N 2 -n 14 ./allreduce 10 100000000

srun -N 2 -n 28 ./allreduce 10 10000
srun -N 2 -n 28 ./allreduce 10 1000000
srun -N 2 -n 28 ./allreduce 10 100000000

srun -N 2 -n 56 ./allreduce 10 10000
srun -N 2 -n 56 ./allreduce 10 1000000
srun -N 2 -n 56 ./allreduce 10 100000000
