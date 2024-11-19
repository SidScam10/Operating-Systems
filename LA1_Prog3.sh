#!/bin/bash
read -p "Enter Limit of Tables: " size
for (( i=1; i<=$size; i++ ));
do
	for (( j=1; j<=$size; j++ ));
	do
		product=$(( i*j ))
		echo -n "$product "
	done
	echo
done
