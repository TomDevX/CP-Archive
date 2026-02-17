/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-17 11:47:31
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Counting Tilings
 *    source: https://cses.fi/problemset/task/2181
 *    submission: https://cses.fi/problemset/result/16290752/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP on Broken Profile
 *    complexity: O(n \cdot m \cdot 2^n)
 *    note: dp[pos][mask] represent the ways to reach that borderline shape (mask) at pos (it will iterate through all cells on table). Just like prefix sum after compressing pos in only 2 dimension instead of dp[i][j][mask]
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
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
ll dp[2][1 << 10];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,m;
    cin >> n >> m;
    dp[0][0] = 1;

    for(int j = 1; j <= m; j++){
        for(int i = 1; i <= n; i++){
            memset(dp[1],0, sizeof(dp[1])); // reset the next dp values
            for(int mask = 0; mask < (1 << n); mask++){
                if(dp[0][mask] == 0) continue;

                // the cell is occupied so in the next column borderline, it will not affect
                if(mask >> (i-1) & 1){
                    dp[1][mask & ~(1 << (i-1))] = (dp[1][mask & ~(1 << (i-1))] + dp[0][mask])%MOD;
                }
                // the cell is not occupied
                else{
                    // vertical
                    if(i < n && !(mask >> i & 1)){
                        dp[1][mask | (1 << i)] = (dp[1][mask ^ (1 << i)] + dp[0][mask])%MOD; // only turn on the below bit to know that the cell is occupied (it will turn off when being iterated through)
                    }
                    // horizontal
                    dp[1][mask | (1 << (i-1))] = (dp[1][mask ^ (1 << (i-1))] + dp[0][mask])%MOD; // turn on current bit so that we know the next column will be occupied
                }
            }
            swap(dp[0],dp[1]);
        }
    }

    cout << dp[0][0];
}