#!/bin/bash

# Empty the csv file on each execution
> "data.txt"

# Generate labels for data
for lbl in $(seq 3 9)
do
	printf "\t"$((2**$lbl)) >> "data.txt"
done

printf "\n" >> "data.txt"

# Compile and execute OpenCL code
for gws in $(seq 10 2 24)
do
	printf $((2**$gws))"\t" >> "data.txt"
	for lws in $(seq 3 9)
	do
		g++ -o first first.cpp -DNUM_ELEMENTS=$((2**$gws)) -DLOCAL_SIZE=$((2**$lws)) -lOpenCL -lm -fopenmp -w
		./first
		printf "\t" >> "data.txt"
	done
	printf "\n" >> "data.txt"
done


