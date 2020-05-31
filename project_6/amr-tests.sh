#!/bin/bash

# Empty the csv file on each execution
> "data1.txt"

# Generate labels for data
for lbl in $(seq 5 8)
do
	printf "\t"$((2**$lbl)) >> "data1.txt"
done

printf "\n" >> "data1.txt"

# Compile and execute OpenCL code
for gws in $(seq 10 2 24)
do
	printf $((2**$gws))"\t" >> "data1.txt"
	for lws in $(seq 5 8)
	do
		g++ -o amr arMultRed.cpp -DNUM_ELEMENTS=$((2**$gws)) -DLOCAL_SIZE=$((2**$lws)) -lOpenCL -lm -fopenmp -w
		./amr
		printf "\t" >> "data1.txt"
	done
	printf "\n" >> "data1.txt"
done


