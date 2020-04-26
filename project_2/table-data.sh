#!/bin/bash

for nn in $(seq 1 12)
do
	for t in 1 2 4 6 8 10	
	do
		g++ -DNUMT=$t -DNUMNODES=$((2**$nn)) main.cpp -o main -lm -fopenmp
		./main
		printf "\t"
	done
	printf "\n"
done
