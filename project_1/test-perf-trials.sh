#!/bin/bash

#Number of threads
for th in $(seq 0 7)
do 	
	# Number of trials
	for t in $(seq 0 7)
	do
		g++ -DNUMT=$((2**$th)) -DNUMTRIALS=$((10**$t)) project-1.cpp -o perf-trials -lm -fopenmp
		./prog
		printf "\t"
	done
	printf "\n"
done
