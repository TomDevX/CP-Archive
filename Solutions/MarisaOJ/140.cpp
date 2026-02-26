/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-26 21:42:21
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Hakurei Shrine
 *    source: https://marisaoj.com/problem/140
 *    submission: https://marisaoj.com/submission/1100620
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: Classic Dynamic Programming problem to count ways to step on stairs. Let dp[i] = ways to step from beginning to stair i_th
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
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
const ll MOD = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;

    vll dp(n+1);
    dp[0] = 1;

    for(int i = 1; i <= n; i++){
        for(int back = 1; back <= 3 && i-back >= 0; back++){
            dp[i] = (dp[i] + dp[i-back])%MOD;
        }
    }
    cout << dp[n];
}