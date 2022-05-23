#!/bin/bash

#
# This script prints all processes that have pages swapped out to disk, along with its respective usage in KB.
#

zero_swap=1	# a control var, that indicates that swap usage is null

_main_()
{
	printf "COMM\tSwap (KB)\n"
	for i in `ls /proc`; do 
		status_file=$(cat /proc/$i/status 2>/dev/null) 
		if [[ -n $status_file ]]; then
			comm=$(/bin/awk '/^Name/ {print $2}' /proc/$i/status)
			swap=$(/bin/awk '/^VmSwap/ {print $2}' /proc/$i/status)
			if [[ $swap -gt 0 ]]; then
				printf "%s\t%s\n" $comm $swap
				zero_swap=0;
			fi
		fi 
	done	

	if [[ $zero_swap -eq 1 ]]; then
		printf "The swap area is empty!\n"
	fi
}

_main_
