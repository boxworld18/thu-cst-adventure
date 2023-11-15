#!/bin/bash

set -x

srun --exclusive ./run_cuda -w conv2 > run.log