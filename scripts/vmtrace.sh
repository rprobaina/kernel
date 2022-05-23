#!/bin/bash

# This script monitors VZS, RSS, huge pages and swap usage of a given @PID process each @TIME seconds.
#
# usage: ./vmtrace <PID> <TIME INTERVAL>

PID="$1"
TIME="$2"
STATUS_FILE="/proc/$PID/status"
COMM=$(/bin/awk '/^Name/ {print $2}' $STATUS_FILE) 

vsz=0
rss=0
hugepages=0
vmswap=0

_get_status_()
{
	vsz=$(/bin/awk '/^VmSize/ {print $2}' $STATUS_FILE)
	rss=$(/bin/awk '/^VmRSS/ {print $2}' $STATUS_FILE)
	hugepages=$(/bin/awk '/^HugetlbPages/ {print $2}' $STATUS_FILE)
	vmswap=$(/bin/awk '/^VmSwap/ {print $2}' $STATUS_FILE)
}

_print_status_()
{
	printf "%d\t%d\t%d\t%d\t\n" $vsz $rss $hugepages $vmswap
}

_main_()
{
	printf "Tracing $COMM. Hit Ctrl + C to finish.\n"
	printf "VSZ\tRSS\tHP\tSwap\n"
	
	while true; do
		_get_status_
		_print_status_
		sleep $TIME	
	done	
}

_main_
