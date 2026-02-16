/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-16 2026-02-16 11:48:10
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Elevator Rides (Approach 2)
 *    source: https://cses.fi/problemset/task/1653/
 *    submission: https://cses.fi/problemset/result/16280676/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Bitmask
 *    complexity: O(n \cdot 2^n)
 *    note: Same as approach 1 but instead of getting child mask, we update the parent masks from the child
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
using vii = vector<vector<int>>;
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

    int n,s;
    cin >> n >> s;

    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<pii> dp(1 << n);
    for(int i = 1; i < (1 << n); i++){
        dp[i] = {1e9,1e9};
    }
    dp[0] = {0,0};

    for(int mask = 0; mask < (1 << n)-1; mask++){
        for(int j = 0; j < n; j++){
            if(!(mask >> j & 1)){
                int i = j+1;
                int par = mask | (1 << j);

                pii stats = (dp[mask].se + a[i] <= s ? make_pair(dp[mask].fi, dp[mask].se + a[i]) : make_pair(dp[mask].fi + 1, a[i]));

                if(stats.fi < dp[par].fi || (stats.fi == dp[par].fi && stats.se < dp[par].se)){
                    dp[par] = stats;
                }
            }
        }
    }

    cout << dp[(1 << n) - 1].fi + (dp[(1 << n) - 1].se > 0);
}