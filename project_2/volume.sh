#!/bin/bash

for nn in 10 25 50 100 250 500 1000 2500 5000
do
	g++ -DNUMNODES=$nn main.cpp -o main -lm -fopenmp
	./main
done
