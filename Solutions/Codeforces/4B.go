/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-09-17 23:01:27
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Before an Exam
 *    source: https://codeforces.com/contest/4/problem/B
 *    submission: https://codeforces.com/contest/4/submission/391051673
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation, Greedy
 *    complexity: O(n)
 *    metacognition:
 *    note: Just check if it possible when total min <= sum <= total max. And then just let all elements be all their min elements and add each up to fill up the sum
**/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

const N = 32

var (
	inp = bufio.NewScanner(os.Stdin)
	out = bufio.NewWriter(os.Stdout)

	a_min [N]int
	a_max [N]int
	a     [N]int
)

func nextStr() string {
	inp.Scan()
	return inp.Text()
}

func nextInt() int {
	x, _ := strconv.Atoi(nextStr())
	return x
}

func main() {
	inp.Split(bufio.ScanWords)
	defer out.Flush()

	days := nextInt()
	sum := nextInt()

	for i := 1; i <= days; i++ {
		a_min[i] = nextInt()
		a[i] = a_min[i]
		a_max[i] = nextInt()

		sum -= a_min[i]
	}

	for i := 1; i <= days; i++ {
		val := min(max(0, sum), a_max[i]-a_min[i])
		sum -= val
		a[i] += val
	}

	if sum != 0 {
		fmt.Fprintln(out, "NO")
		return
	}

	fmt.Fprintln(out, "YES")
	for i := 1; i <= days; i++ {
		fmt.Fprint(out, a[i], " ")
	}
}
