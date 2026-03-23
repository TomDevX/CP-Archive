/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-23 09:31:36
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: HÀNH TRÌNH RẺ NHẤT 
 *    source: KT_20260323.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()

// --- [ TYPES & ALIASES ] ---
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("TSB.INP", "r")) return;
    freopen("TSB.INP", "r", stdin);
    freopen("TSB.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 20;
ll dis[N+1][N+1];
ll dp[1 << N][N+1];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(dp,0x3f,sizeof(dp));
    
    int n;
    cin >> n;
    for(int u = 1; u <= n; u++){
        for(int v = 1; v <= n; v++){
            cin >> dis[u][v];
        }
    }

    dp[1][1] = 0;

    for(int mask = 1; mask < (1 << n); mask++){
        for(int u = 1; u <= n; u++){
            if(dp[mask][u] != dp[0][0] && mask >> (u-1) & 1){
                for(int v = 1; v <= n; v++){
                    if(!(mask >> (v-1) & 1)) dp[mask | (1 << (v-1))][v] = min(dp[mask | (1 << (v-1))][v], dp[mask][u] + dis[u][v]);
                }
            }
        }
    }

    ll ans = 2e18;
    int new_mask = (1 << n) - 1;
    for(int i = 2; i <= n; i++){
        if(dp[new_mask][i] != dp[0][0]) ans = min(ans, dp[new_mask][i] + dis[i][1]);
    }

    cout << (ans == 2e18 ? -1 : ans);
    
    return NAH_I_WOULD_WIN;
}