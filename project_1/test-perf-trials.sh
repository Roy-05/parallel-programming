#!/bin/bash

> "data1.txt"

for th in 1 2 4 8
do
	printf "\t"$th >> "data1.txt"
done

printf "\n" >> "data1.txt"


# Number of trials
for t in $(seq 14 20)
do
	printf $((2**$t))"\t" >> "data1.txt"
	#Number of threads
	for th in 1 2 4 8
	do 	
		g++ -DNUMT=$th -DNUMTRIALS=$((2**$t)) project-1.cpp -o perf-trials -lm -fopenmp
		./perf-trials
		printf "\t" >> "data1.txt"
	done
	printf "\n" >> "data1.txt"
done
