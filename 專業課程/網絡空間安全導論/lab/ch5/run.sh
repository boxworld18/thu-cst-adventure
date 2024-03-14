#!/bin/bash

file1="testcases/test.txt"
file2="testcases/result.txt"
file3="testcases/tmp.txt"

mkdir testcases/
make
./paillier < $file1 > $file3

if diff "$file2" "$file3" >/dev/null ; then
    echo "Validation Passed"
else
    echo "Validation Failed"
fi