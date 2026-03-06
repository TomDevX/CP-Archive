/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-05 23:32:47
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Reading 2
 *    source: https://marisaoj.com/problem/159
 *    submission: https://marisaoj.com/submission/1111932
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n \cdot k)
 *    note: Multiply the previous ways with the current book in the i shelf and we get the ways
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
const ll MOD = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,k;
    cin >> n >> k;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vvll dp(n+1,vll(k+1));
    for(int i = 0; i <= n; i++) dp[i][0] = 1;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= min(k,i); j++){
            dp[i][j] = (1LL*a[i]*dp[i-1][j-1] + dp[i-1][j])%MOD;
        }
    }

    cout << dp[n][k];
}