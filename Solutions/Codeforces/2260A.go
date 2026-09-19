//go:build ignore

/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-09-19 22:42:52
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Monocarp's Contest
 *    source: https://codeforces.com/contest/2260/problem/A
 *    submission: https://codeforces.com/contest/2260/submission/391247538
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    metacognition:
 *    note: Just check as the problem says
 **/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

// ----------------------- [ CONFIG ] -----------------------
const N = 52

var (
	inp *bufio.Scanner
	out *bufio.Writer

	a [N]int
)

func nextStr() string {
	inp.Scan()
	return inp.Text()
}

func nextInt() int {
	x, _ := strconv.Atoi(nextStr())
	return x
}

func nextInt64() int64 {
	x, _ := strconv.ParseInt(nextStr(), 10, 64)
	return x
}

func setup() {
	inpFile := "2260A.INP"
	outFile := "2260A.OUT"

	if fIn, err := os.Open(inpFile); err == nil {
		inp = bufio.NewScanner(fIn)
		if fOut, err := os.Create(outFile); err == nil {
			out = bufio.NewWriter(fOut)
		} else {
			out = bufio.NewWriter(os.Stdout)
		}
	} else {
		inp = bufio.NewScanner(os.Stdin)
		out = bufio.NewWriter(os.Stdout)
	}

	inp.Split(bufio.ScanWords)
	inp.Buffer(make([]byte, 1024), 1e7)
}

func btoi(b bool) int {
	if b {
		return 1
	}
	return 0
}

// ----------------------- [ SOLVE ] -----------------------
func solve() {
	n := nextInt()
	for i := 1; i <= n; i++ {
		a[i] = nextInt()
	}

	need := btoi(a[1] == 1) + btoi(a[n] == 1)
	easy := 0

	for i := 2; i < n; i++ {
		easy += btoi(a[i] == 0)
	}

	if easy < need {
		fmt.Fprintln(out, -1)
		return
	}

	fmt.Fprintln(out, need)
}

func main() {
	setup()
	defer out.Flush()

	tc := 1
	tc = nextInt()
	for t := 1; t <= tc; t++ {
		solve()
	}
}
