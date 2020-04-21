#!/bin/bash

#Number of threads
for th in $(seq 0 7)
do
	g++ -DNUMT=$((2**$th)) -DNUMTRIALS=$((10**8)) project-1.cpp -o perfs -lm -fopenmp
	./perfs
done
