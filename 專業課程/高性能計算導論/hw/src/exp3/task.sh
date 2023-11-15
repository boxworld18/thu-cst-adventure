#!/bin/bash

set -x

make -j 4
srun -N 1 ./omp_sched
