#!/bin/bash

#Number of threads
for th in 1 2 4 6 8 10 12
do 	
	# Number of trials
	for t in $(seq 0 7)
	do
		g++ -DNUMT=$th -DNUMTRIALS=$((10**$t)) project-1.cpp -o perf-trials -lm -fopenmp
		./perf-trials
		printf "\t"
	done
	printf "\n"
done
