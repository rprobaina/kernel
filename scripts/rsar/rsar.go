package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"strings"
	"time"
)

var (
	DEFAULT_SAMPLES  int    = 1
	DEFAULT_INTERVAL int    = 1
	PROCDIR          string = "/proc"
	PROCDIR_LOADAVG  string = "/proc/loadavg"
	PROCDIR_MEMINFO  string = "/proc/meminfo"
	PROCDIR_SWAPS    string = "/proc/swaps"
	STATUSFILE       string = "stat"
)

type loadavg struct {
	avg01 string
	avg05 string
	avg15 string
	runq  string
	pcnt  string
}

type meminfo struct {
	total             string
	free              string
	available         string
	buffers           string
	cached            string
	swapCached        string
	active            string
	inactive          string
	activeAnon        string
	inactiveAnon      string
	activeFile        string
	inactiveFile      string
	unevictable       string
	locked            string
	swapTotal         string
	swapFree          string
	dirty             string
	writeback         string
	anonPages         string
	mapped            string
	shmem             string
	reclaimable       string
	slab              string
	sReclaimable      string
	sUnreclaim        string
	kernelStack       string
	pageTables        string
	nfsUnstable       string
	bounce            string
	writebackTmp      string
	commitLimit       string
	committedAS       string
	vmallocTotal      string
	vmallocUsed       string
	vmallocChunk      string
	percpu            string
	hardwareCorrupted string
	anonHugePages     string
	shmemHugePages    string
	shmemPmdMapped    string
	fileHugePages     string
	filePmdMapped     string
	hugePagesTotal    string
	hugePagesFree     string
	hugePagesRsvd     string
	hugePagesSurp     string
	hugepagesize      string
	hugetlb           string
	directMap4k       string
	directMap2M       string
	directMap1G       string
}

type swaps struct {
	filename string
	swaptype string
	size     string
	used     string
	priority string
}

type procstat struct {
	pid                   string
	comm                  string
	state                 string
	ppid                  string
	pgrp                  string
	session               string
	tty_nr                string
	tpgid                 string
	flags                 string
	minflt                string
	cminflt               string
	majflt                string
	cmajflt               string
	utime                 string
	stime                 string
	cutime                string
	cstime                string
	priority              string
	nice                  string
	num_threads           string
	itrealvalue           string
	starttime             string
	vsize                 string
	rss                   string
	rsslim                string
	startcode             string
	endcode               string
	startstack            string
	kstkesp               string
	kstkeip               string
	signal                string
	blocked               string
	sigignore             string
	sigcatch              string
	wchan                 string
	nswap                 string
	cnswap                string
	exit_signal           string
	processor             string
	rt_priority           string
	policy                string
	delayacct_blkio_ticks string
	guest_time            string
	cguest_time           string
	start_data            string
	end_data              string
	start_brk             string
	arg_start             string
	arg_end               string
	env_start             string
	env_end               string
	exit_code             string
}

/* get_loadavg: */
func _get_loadavg() loadavg {

	var l loadavg

	dat, err := os.ReadFile(PROCDIR_LOADAVG)
	if err != nil {
		fmt.Printf("Error reading %s\n", PROCDIR_LOADAVG)
	}

	dat_s := strings.Split(string(dat), " ")

	l.avg01 = dat_s[0]
	l.avg05 = dat_s[1]
	l.avg15 = dat_s[2]
	l.runq = strings.Split(dat_s[3], "/")[0]
	l.pcnt = strings.Split(dat_s[3], "/")[1]

	return l
}

func _get_meminfo() meminfo {

	var m meminfo

	dat, err := os.ReadFile(PROCDIR_MEMINFO)
	if err != nil {
		fmt.Printf("Error reading %s\n", PROCDIR_MEMINFO)
		/* FIXME panic or return error value */
	}

	dat_s := strings.Split(string(dat), "\n")

	m.total = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[0])), " "), " ")[1]
	m.free = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " "), " ")[1]
	m.available = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[2])), " "), " ")[1]
	m.buffers = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[3])), " "), " ")[1]
	m.cached = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[4])), " "), " ")[1]
	m.swapCached = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[5])), " "), " ")[1]
	m.active = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[6])), " "), " ")[1]
	m.inactive = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[7])), " "), " ")[1]
	m.activeAnon = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[8])), " "), " ")[1]
	m.inactiveAnon = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[9])), " "), " ")[1]
	m.activeFile = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[10])), " "), " ")[1]
	m.inactiveFile = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[11])), " "), " ")[1]
	m.unevictable = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[12])), " "), " ")[1]
	m.locked = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[13])), " "), " ")[1]
	m.swapTotal = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[14])), " "), " ")[1]
	m.swapFree = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[15])), " "), " ")[1]
	m.dirty = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[16])), " "), " ")[1]
	m.writeback = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[17])), " "), " ")[1]
	m.anonPages = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[18])), " "), " ")[1]
	m.mapped = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[19])), " "), " ")[1]
	m.shmem = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[20])), " "), " ")[1]
	m.reclaimable = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[21])), " "), " ")[1]
	m.slab = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[22])), " "), " ")[1]
	m.sReclaimable = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[23])), " "), " ")[1]
	m.sUnreclaim = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[24])), " "), " ")[1]
	m.kernelStack = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[25])), " "), " ")[1]
	m.pageTables = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[26])), " "), " ")[1]
	m.nfsUnstable = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[27])), " "), " ")[1]
	m.bounce = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[28])), " "), " ")[1]
	m.writebackTmp = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[29])), " "), " ")[1]
	m.commitLimit = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[30])), " "), " ")[1]
	m.committedAS = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[31])), " "), " ")[1]
	m.vmallocTotal = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[32])), " "), " ")[1]
	m.vmallocUsed = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[33])), " "), " ")[1]
	m.vmallocChunk = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[34])), " "), " ")[1]
	m.percpu = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[35])), " "), " ")[1]
	m.hardwareCorrupted = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[36])), " "), " ")[1]
	m.anonHugePages = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[37])), " "), " ")[1]
	m.shmemHugePages = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[38])), " "), " ")[1]
	m.shmemPmdMapped = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[39])), " "), " ")[1]
	m.hugePagesTotal = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[40])), " "), " ")[1]
	m.hugePagesFree = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[41])), " "), " ")[1]
	m.hugePagesRsvd = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[42])), " "), " ")[1]
	m.hugePagesSurp = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[43])), " "), " ")[1]
	m.hugepagesize = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[44])), " "), " ")[1]
	m.hugetlb = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[45])), " "), " ")[1]
	m.directMap4k = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[46])), " "), " ")[1]
	m.directMap2M = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[47])), " "), " ")[1]
	m.directMap1G = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[48])), " "), " ")[1]

	return m
}

func _get_swaps() swaps {

	var s swaps

	dat, err := os.ReadFile(PROCDIR_SWAPS)
	if err != nil {
		fmt.Printf("Error reading %s\n", PROCDIR_SWAPS)
	}

	dat_s := strings.Split(string(dat), "\n")

	s.filename = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " "), " ")[0]
	s.swaptype = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " "), " ")[1]
	s.size = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " "), " ")[2]
	s.used = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " "), " ")[3]
	s.priority = strings.Split(strings.Join(strings.Fields(strings.TrimSpace(dat_s[1])), " "), " ")[4]

	return s
}

/* _get_pps:
	collects per-process stats from /proc/PID/stat file
	and return a slice of procstat, containing per-process
	information of all running processes in the system.
	ps.: it doesn't have self stats, though.
*/
func _get_pps() []procstat {

	var pps_s []procstat

	files, err := ioutil.ReadDir(PROCDIR)
	if err != nil {
		fmt.Printf("Error reading %s\n", PROCDIR)
	}

	// walking over /proc
	for _, f := range files {
		if f.Name() == "acpi" { // acpi is the first directory after the last PID
			break
		}

		pf := PROCDIR + "/" + f.Name() + "/" + STATUSFILE

		dat, err := os.ReadFile(pf)
		if err != nil {
			fmt.Printf("Error reading %s\n", PROCDIR_SWAPS)
			continue
		}

		dat_s := strings.Split(string(dat), " ")

		var p procstat
		p.pid = dat_s[0]
		p.comm = dat_s[1]
		p.state = dat_s[2]
		p.ppid = dat_s[3]
		p.pgrp = dat_s[4]
		p.session = dat_s[5]
		p.tty_nr = dat_s[6]
		p.tpgid = dat_s[7]
		p.flags = dat_s[8]
		p.minflt = dat_s[9]
		p.cminflt = dat_s[10]
		p.majflt = dat_s[11]
		p.cmajflt = dat_s[12]
		p.utime = dat_s[13]
		p.stime = dat_s[14]
		p.cutime = dat_s[15]
		p.cstime = dat_s[16]
		p.priority = dat_s[17]
		p.nice = dat_s[18]
		p.num_threads = dat_s[19]
		p.itrealvalue = dat_s[20]
		p.starttime = dat_s[21]
		p.vsize = dat_s[22]
		p.rss = dat_s[23]
		p.rsslim = dat_s[24]
		p.startcode = dat_s[25]
		p.endcode = dat_s[26]
		p.startstack = dat_s[27]
		p.kstkesp = dat_s[28]
		p.kstkeip = dat_s[29]
		p.signal = dat_s[30]
		p.blocked = dat_s[31]
		p.sigignore = dat_s[32]
		p.sigcatch = dat_s[33]
		p.wchan = dat_s[34]
		p.nswap = dat_s[35]
		p.cnswap = dat_s[36]
		p.exit_signal = dat_s[37]
		p.processor = dat_s[38]
		p.rt_priority = dat_s[39]
		p.policy = dat_s[40]
		p.delayacct_blkio_ticks = dat_s[41]
		p.guest_time = dat_s[42]
		p.cguest_time = dat_s[43]
		p.start_data = dat_s[44]
		p.end_data = dat_s[45]
		p.start_brk = dat_s[46]
		p.arg_start = dat_s[47]
		p.arg_end = dat_s[48]
		p.env_start = dat_s[49]
		p.env_end = dat_s[50]
		p.exit_code = dat_s[51]

		// Append p element into pps_s slice
		pps_s = append(pps_s, p)
	}
	return pps_s
}

/*******************/
/* PRINT FUNCTIONS */
/*******************/

func _print_loadavg(l loadavg) {
	t := time.Now()
	fmt.Printf(t.Format("15:10:05")+" %s\t%s\t%s\t%s\t%s\n", l.pcnt, l.runq, l.avg01, l.avg05, l.avg15)
}

func _print_meminfo(m meminfo) {
	var err error
	var tot, free float64
	t := time.Now()

	tot, err = strconv.ParseFloat(m.total, 32)
	if err != nil {
		fmt.Printf("Erro parsing %s to float", m.total)
	}

	free, err = strconv.ParseFloat(m.free, 32)
	if err != nil {
		fmt.Printf("Erro parsing %s to float", m.free)
	}

	used := 100 * (tot - free) / tot

	fmt.Printf(t.Format("15:10:05")+" %s\t%s\t%.2f\t%s\t\t%s\t%s\n", m.total, m.free, used, m.available, m.buffers, m.cached)
}

func _print_swaps(s swaps) {
	t := time.Now()
	fmt.Printf(t.Format("15:10:05")+" %s\t%s\n", s.size, s.used)
}

func _print_pps(pps_s []procstat) {
	t := time.Now()
	for _, p := range pps_s {
		fmt.Printf(t.Format("15:10:05")+" %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
			p.pid, p.comm, p.state, p.utime, p.stime, p.vsize, p.rss, p.nswap)
			// FIXME - TODO
			// - calc %usr, based on utime
			// - calc %sys, based on stime
			// - find a way to tabulate it better
	}
}

func loadavg_header() {
	fmt.Println("\t pcnt\trunq\tavg01\tavg05\tavg15")
}

func mem_header() {
	fmt.Printf("\t memtot\t\tmemfree\tmemused\tmemavail\tbuffers\tcached\n")
}

func swap_header() {
	fmt.Printf("\t swap total\tswap used\n")
}

func pps_header() {
	fmt.Printf("\t pid\tcomm\t\tstate\tusr\tsys\tvsz\trss\tswap\n")
}

func loadavg_stat() {
	l := _get_loadavg()
	_print_loadavg(l)
}

func mem_stat() {
	m := _get_meminfo()
	_print_meminfo(m)
}

func swap_stat() {
	s := _get_swaps()
	_print_swaps(s)
}

func pps_stat() {
	pps_s := _get_pps() // pps_s is a slice
	_print_pps(pps_s)
}

func help() {
	fmt.Println("")
	fmt.Println("\t\t\tRSAR Help")
	fmt.Println("")
	fmt.Println("\tUsage:")
	fmt.Println("\t\t./rsar --<option> <samples> <interval> \n\n")
	fmt.Println("\tOptions:")
	fmt.Println("\t\t--help: to get help")
	fmt.Println("\t\t--all: all statistics")
	fmt.Println("\t\t--load: load average statistics")
	fmt.Println("\t\t--cpu: CPU statistics")
	fmt.Println("\t\t--mem: memory statistics")
	fmt.Println("\t\t--swap: swap statistics")
	fmt.Println("\t\t--proc: process state statistics")
	fmt.Println("\t\t--pps: per process statistics")
	fmt.Println("")
}

func main() {

	var err error
	args := os.Args
	samples := DEFAULT_SAMPLES
	interval := DEFAULT_INTERVAL

	if len(args) < 2 || args[1] == "--help" {
		help()
		os.Exit(0)
	}

	if len(args) == 4 {
		samples, err = strconv.Atoi(args[2])
		interval, err = strconv.Atoi(args[3])
		if err != nil {
			// FIXME
		}
	}

	switch args[1] {
	case "--load":
		loadavg_header()
		for i := 0; i < samples; i++ {
			loadavg_stat()
			time.Sleep(time.Duration(interval) * time.Second)
		}
	case "--mem":
		mem_header()
		for i := 0; i < samples; i++ {
			mem_stat()
			time.Sleep(time.Duration(interval) * time.Second)
		}
	case "--swap":
		swap_header()
		for i := 0; i < samples; i++ {
			swap_stat()
			time.Sleep(time.Duration(interval) * time.Second)
		}
	case "--pps":
		pps_header()
		for i := 0; i < samples; i++ {
			pps_stat()
			time.Sleep(time.Duration(interval) * time.Second)
		}
	default:
		fmt.Println(args[1] + " is an invalid option!")
		help()
	}

}
