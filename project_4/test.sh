#!/bin/bash

for s in $(seq 10 23)
do
	g++ main.cpp -o main -fopenmp -DSIZE=$((2**$s))
	./main
done
