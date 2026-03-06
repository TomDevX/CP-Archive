/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-06 20:20:34
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Longest increasing subsequence
 *    source: https://marisaoj.com/problem/143
 *    submission: https://marisaoj.com/submission/1112864
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n \log n)
 *    note: Typical LIS
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using pii = pair<int,int>;
using pill = pair<int,long long>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int ans = 0;
    vi lis(n+1,2e9);
    lis[0] = 0;
    
    for(int i = 1; i <= n; i++){
        int it = lower_bound(all(lis,1), a[i]) - lis.begin();
        ans = max(ans,it);
        lis[it] = a[i];
    }
    cout << ans;
}