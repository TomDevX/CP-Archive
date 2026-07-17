/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-16 11:04:13
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Elevator Rides (Approach 1)
 *    source: https://cses.fi/problemset/task/1653/
 *    submission: https://cses.fi/problemset/result/16280676/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Bitmask
 *    complexity: O(n \cdot 2^n)
 *    note: With any greedy method, we cant know that which is the correct element that we should choose, so that should give us a WA. So with bitmask, the mask on the DP will store the index of served passengers (1 = served, 0 = untouched). The DP will save {number of rides, weight used} as a pair.
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

    int n, s;
    cin >> n >> s;

    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    vector<pii> dp(1<<n);
    dp[0] = {0,0};

    for(int mask = 1; mask < (1 << n); mask++){
        dp[mask] = {1e9,1e9};
        for(int submask = mask; submask; submask &= (submask - 1)){ // iterate through every bit 1
            int j = __builtin_ctz(submask) + 1; // get the last index 1-based
            int child = mask & ~((submask & -submask)); // turn off the bit at index j 1-based

            pii stats = (dp[child].se + a[j] <= s ? make_pair(dp[child].fi,dp[child].se + a[j]) : make_pair(dp[child].fi + 1, a[j])); // chaging status formula
            
            if(dp[mask].fi > stats.fi || (dp[mask].fi == stats.fi && dp[mask].se > stats.se)){
                dp[mask] = stats; // if the child is more optimized, we use it
            }
        }
    }

    cout << dp[(1 << n) - 1].fi + (dp[(1<<n) - 1].se > 0); // if there is still weight, it means that we need 1 more ride
}