#!/bin/bash

# Number of threads
for th in $(seq 0 7)
do	
	printf "\nThread Number: %d\n" "$((2**$th))"
	#Number of trials
	for t in 1 5 10 50 100 500 1000 5000 10000 50000 100000 500000 1000000 5000000 10000000
	do
		g++ -DNUMT=$((2**$th)) -DNUMTRIALS=$t project-1.cpp -o prog -lm -fopenmp
		./prog
	done
done
