#!/bin/bash

for t in 1 2 4 6 8 	
do
	for nn in 5 10 25 50 100 250 500 1000
	do
		g++ -DNUMT=$t -DNUMNODES=$nn main.cpp -o main -lm -fopenmp
		./main
		printf "\t"
	done
	printf "\n"
done
