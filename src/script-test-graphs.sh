#!/bin/bash

for item in ../graphs/graph*.txt
do
	echo "Determine Connected Components on $item" 
  ./connected $item > ./$item.out
done


