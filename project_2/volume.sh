#!/bin/bash

for nn in $(seq 100 100 1000)
do
	g++ -DNUMNODES=$nn main.cpp -o main -lm -fopenmp
	./main
done
