#!/bin/bash
set -x
set -e

make -j
srun ./aplusb
