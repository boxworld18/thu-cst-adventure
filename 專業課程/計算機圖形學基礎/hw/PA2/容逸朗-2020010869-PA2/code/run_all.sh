#!/usr/bin/env bash

# If project not ready, generate cmake file.
if [[ ! -d build ]]; then
    echo "good"
else
    rm -rf build
fi
mkdir -p build
cd build
cmake ..
make -j
cd ..

#!/usr/bin/env bash
mkdir -p output
bin/PA2 testcases/scene01_basic.txt output/scene01.bmp
bin/PA2 testcases/scene04_axes.txt output/scene04.bmp
bin/PA2 testcases/scene06_bunny_1k.txt output/scene06.bmp
bin/PA2 testcases/scene08_core.txt output/scene08.bmp
bin/PA2 testcases/scene09_norm.txt output/scene09.bmp
bin/PA2 testcases/scene10_wineglass.txt output/scene10.bmp
