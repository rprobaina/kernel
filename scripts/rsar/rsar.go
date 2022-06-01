package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

var (
	PROCDIR_LOADAVG string = "/proc/loadavg"
	PROCDIR_MEMINFO string = "/proc/meminfo"
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

/* get_loadavg: */
func get_loadavg() loadavg {

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

func get_meminfo() meminfo {

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

func print_loadavg(l loadavg) {
	fmt.Println("pcbt\trunq\tavg01\tavg05\tavg15")
	fmt.Printf("%s\t%s\t%s\t%s\t%s\n", l.pcnt, l.runq, l.avg01, l.avg05, l.avg15)
}

func print_meminfo(m meminfo) {
	var err error
	var tot, free float64

	tot, err = strconv.ParseFloat(m.total, 32)
	if err != nil {
		fmt.Printf("Erro parsing %s to float", m.total)
	}

	free, err = strconv.ParseFloat(m.free, 32)
	if err != nil {
		fmt.Printf("Erro parsing %s to float", m.free)
	}

	used := 100 * (tot - free) / tot

	fmt.Printf("memtot\tmemfree\tmemused\tmemavail\tbuffers\tcached\n")
	fmt.Printf("%s\t%s\t%.2f\t%s\t\t%s\t%s\n", m.total, m.free, used, m.available, m.buffers, m.cached)
}

func main() {
	l := get_loadavg()
	print_loadavg(l)

	fmt.Println(" ")

	m := get_meminfo()
	print_meminfo(m)

	fmt.Println(m)

}
