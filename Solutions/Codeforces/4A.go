//go:build ignore

/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-09-17 23:56:08
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Watermelon
 *    source: https://codeforces.com/contest/4/problem/A
 *    submission: https://codeforces.com/contest/4/submission/390997036
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(1)
 *    metacognition:
 *    note: Just need to consider the case of n = 2, else check even/odd
 **/

package main

import (
	"fmt"
)

func main() {
	var x int

	fmt.Scan(&x)

	if x%2 == 0 && x != 2 {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}
