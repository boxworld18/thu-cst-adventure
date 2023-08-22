#!/bin/sh

FILES= ./*
for f in $FILES
do
    fn=$(basename "$f")
    printf "$fn"
    pg=$(sudo qpdf --show-npages "$f")
    printf ",$pg\n"
done
