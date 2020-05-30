#!/bin/bash

for gws in $(seq 10 2 26)
do
	for lws in $(seq 3 9)
	do
		g++ -o first first.cpp -DNUM_ELEMENTS=$((2**$gws)) -DLOCAL_SIZE=$((2**$lws)) -lOpenCL -lm -fopenmp -w
		./first
	done
done


