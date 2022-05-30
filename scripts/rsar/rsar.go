package main

import (
	"fmt"
	"os"
	"strings"
)

var PROCDIR_LOADAVG string = "/proc/loadavg"

type loadavg struct {
	avg01 string
	avg05 string
	avg15 string
	runq string
	pcnt string
}

/* get_loadavg: */
func get_loadavg() loadavg {

	var l loadavg

	dat, err := os.ReadFile(PROCDIR_LOADAVG)
	if (err != nil){
		fmt.Printf("Error reading %s\n", PROCDIR_LOADAVG)
		/* FIXME panic or return error value */
	}

	var dat_s = strings.Split(string(dat), " ")

	l.avg01 = dat_s[0]
	l.avg05 = dat_s[1]
	l.avg15 = dat_s[2]
	l.runq = strings.Split(dat_s[3], "/")[0]
	l.pcnt = strings.Split(dat_s[3], "/")[1]

	return l
}

func ptr_loadavg(l loadavg) {
	fmt.Println("pcbt\trunq\tavg01\tavg05\tavg15")
	fmt.Printf("%s\t%s\t%s\t%s\t%s\n", l.pcnt, l.runq, l.avg01, l.avg05, l.avg15)
}

func main() {
	var l = get_loadavg()
	ptr_loadavg(l)
}
