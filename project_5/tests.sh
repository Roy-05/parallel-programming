#!/bin/bash

> "data.txt"

for lbl in $(seq 4 7)
do
	printf "\t"$((2**$lbl)) >> "data.txt"
done

printf "\n" >> "data.txt"

for tr in $(seq 14 20)
do
	printf $((2**$tr))"\t" >> "data.txt"
	for bl in $(seq 4 7)
	do	
		nvcc -o main -DBLOCKSIZE=$((2**$bl)) -DNUMTRIALS=$((2**$tr)) montecarlo.cu
		./main
		printf "\t" >> "data.txt"
	done
	printf "\n" >> "data.txt"
done
