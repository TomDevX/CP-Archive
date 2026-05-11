/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-11 20:43:06
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Average Score of Tourist Routes
 *    source: https://atcoder.jp/contests/awc0066/tasks/awc0066_e
 *    submission: https://atcoder.jp/contests/awc0066/submissions/75731335
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(n \cdot 2^n)
 *    note: Let dp[mask][u] represent as visited nodes ending at u, then we just need to count the total sum and ways for each states.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <iomanip>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
    if(!fopen("awc0066_e.INP", "r")) return;
    freopen("awc0066_e.INP", "r", stdin);
    freopen("awc0066_e.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 20;

ll val[N];
pll dp[1 << N][N];
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,m,st,ed;
    cin >> n >> m >> st >> ed;

    for(int i = 1; i <= n; i++) cin >> val[i];

    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dp[1 << (st-1)][st] = {val[st],1};

    for(int mask = (1 << (st-1)); mask < (1 << n); mask++){
        for(int u = 1; u <= n; u++){
            if(dp[mask][u].se == 0) continue;

            if(mask >> (u-1) & 1){
                for(int v : adj[u]){
                    if(mask >> (v-1) & 1) continue;
                    dp[mask | (1 << (v-1))][v].fi += dp[mask][u].fi + dp[mask][u].se*val[v];
                    dp[mask | (1 << (v-1))][v].se += dp[mask][u].se;
                }
            }
        }
    }

    ll sum = 0;
    ll cnt = 0;
    
    for(int mask = 1; mask < (1 << n); mask++){
        if(mask >> (ed - 1) & 1){
            sum += dp[mask][ed].fi;
            cnt += dp[mask][ed].se;
        }
    }

    cout << fixed << setprecision(15) << 1.0L*sum/(1.0L*cnt);
    
    return NAH_I_WOULD_WIN;
}