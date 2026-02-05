/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-11-22 22:01:50
 *    country: Vietnam - VNM
 *    title: Dãy con tăng dài nhất (bản dễ) 
 *    source: 
 *    submission: https://oj.vnoi.info/src/10967418
 * ----------------------------------------------------------
 *    algorithm: Dynamic Programming, Binary Search
 *    complexity: O(n\logn)
 *    note:
 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <cstring>
#include <bitset>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

int main(){
    fast();
    //setup();
    
    int n;
    cin >> n;
    vector<int> a(n+1);

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    vector<int> dp(n+1), lis(n+1,1e9+1);

    for(int i =1 ; i<= n; i++){
        vector<int>::iterator it = lower_bound(all(lis,1),a[i]);
        dp[i] = it-lis.begin();
        *it = a[i];
    }

    cout << *max_element(all(dp,1));
}
