#!/bin/bash

make clean
make UNROLL_N=1
./main

make clean
make UNROLL_N=2
./main

make clean
make UNROLL_N=4
./main

make clean
make UNROLL_N=8
./main

make clean
make UNROLL_N=16
./main