#!/bin/bash

# This script monitors hugepages statistics.
#
# usage: ./hugepages_monitor <TIME INTERVAL>

TIME=${1:-5}
HPSYS_DIR="/sys/kernel/mm/hugepages/"
PMD_HUGE="hugepages-2048kB"
PUD_HUGE="hugepages-1048576kB"

free_hugepages=0
nr_hugepages=0
nr_hugepages_mempolicy=0
nr_overcommit_hugepages=0
resv_hugepages=0
surplus_hugepages=0

_get_status_()
{
	hpsize="$1"
	free_hugepages=$(cat $HPSYS_DIR/$hpsize/free_hugepages)
	nr_hugepages=$(cat $HPSYS_DIR/$hpsize/nr_hugepages)
	nr_hugepages_mempolicy=$(cat $HPSYS_DIR/$hpsize/nr_hugepages_mempolicy)
	nr_overcommit_hugepages=$(cat $HPSYS_DIR/$hpsize/nr_overcommit_hugepages)
	resv_hugepages=$(cat $HPSYS_DIR/$hpsize/resv_hugepages)
	surplus_hugepages=$(cat $HPSYS_DIR/$hpsize/surplus_hugepages)
}

_print_status_()
{
	printf "%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n" $free_hugepages $nr_hugepages $nr_hugepages_mempolicy $nr_overcommit_hugepages $resv_hugepages $surplus_hugepages
}

_main_()
{
	printf "Monitoring Huge Pages usage, eacht $TIME senconds. Hit Ctrl + C to finish.\n"
	printf "type\tfree\tnr\t\tnr_mempolicy\tnr_overcommit\tresv\t\tsurplus\n"
	
	while true; do
		printf "2MB\t"
		_get_status_ $PMD_HUGE
		_print_status_
	
		printf "1GB\t"
		_get_status_ $PUD_HUGE
		_print_status_
		
		sleep $TIME	
	done	
}

_main_
