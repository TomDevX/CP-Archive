/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-05 23:25:33
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Buying tickets
 *    source: https://marisaoj.com/problem/572
 *    submission: https://marisaoj.com/submission/1111914
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: At each option we have 2 ways to choose: buy only for person i and buy for both person i and i-1
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
    vi a(n+1), t(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i < n; i++) cin >> t[i];

    vll dp(n+1);
    dp[1] = a[1];
    for(int i = 2; i <= n; i++){
        dp[i] = min(dp[i-1] + a[i], dp[i-2] + t[i-1]);
    }
    cout << dp[n];
}