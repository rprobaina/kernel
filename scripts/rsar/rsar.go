package main

import (
	"fmt"
	"os"
	"strings"
	"strconv"
)

var PROCDIR_LOADAVG string = "/proc/loadavg"
var PROCDIR_MEMINFO string = "/proc/meminfo"

type loadavg struct {
	avg01 string
	avg05 string
	avg15 string
	runq string
	pcnt string
}

type meminfo struct {
	total string
	free string
	available string
	buffers string
	cached string
}

/* get_loadavg: */
func get_loadavg() loadavg {

	var l loadavg

	dat, err := os.ReadFile(PROCDIR_LOADAVG)
	if (err != nil){
		fmt.Printf("Error reading %s\n", PROCDIR_LOADAVG)
		/* FIXME panic or return error value */
	}

	dat_s := strings.Split(string(dat), " ")

	l.avg01 = dat_s[0]
	l.avg05 = dat_s[1]
	l.avg15 = dat_s[2]
	l.runq = strings.Split(dat_s[3], "/")[0]
	l.pcnt = strings.Split(dat_s[3], "/")[1]

	return l
}

func get_meminfo() meminfo {

	var m meminfo

	dat, err := os.ReadFile(PROCDIR_MEMINFO)
	if (err != nil){
		fmt.Printf("Error reading %s\n", PROCDIR_MEMINFO)
		/* FIXME panic or return error value */
	}

	dat_s := strings.Split(string(dat), "\n")

	m.total = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[0])), " ") , " ")[1]
	m.free = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " ") , " ")[1]
	m.available = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[2])), " ") , " ")[1]
	m.buffers = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[3])), " ") , " ")[1]
	m.cached = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[4])), " ") , " ")[1]

	return m
}

func print_loadavg(l loadavg) {
	fmt.Println("pcbt\trunq\tavg01\tavg05\tavg15")
	fmt.Printf("%s\t%s\t%s\t%s\t%s\n", l.pcnt, l.runq, l.avg01, l.avg05, l.avg15)
}

func print_meminfo(m meminfo) {
	var err error	
	var tot, free float64
	
	tot, err = strconv.ParseFloat(m.total, 32)
	if (err != nil) {
		fmt.Printf("Erro parsing %s to float", m.total)
	}

	free, err = strconv.ParseFloat(m.free, 32)
	if (err != nil) {
		fmt.Printf("Erro parsing %s to float", m.free)
	}

	used := 100 * ((tot - free) / tot)

	fmt.Printf("memtot\tmemfree\tmemused\tmemavail\tbuffers\tcached\n")
	fmt.Printf("%s\t%s\t%.2f\t%s\t\t%s\t%s\n", m.total, m.free, used, m.available, m.buffers, m.cached)
}

func main() {
	l := get_loadavg()
	print_loadavg(l)

	fmt.Println(" ")

	m := get_meminfo()
	print_meminfo(m)

}
