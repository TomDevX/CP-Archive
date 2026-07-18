/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-18 20:36:57
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: TRIP
 *    source: https://oj.vnoi.info/problem/lem3
 *    submission: https://oj.vnoi.info/submission/12768469
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(2 ^ n \cdot n^2)
 *    metacognition: Let dp[mask][cur] = min cost to visit all nodes in mask and last stop is node cur. Transitions using dp[mask turn on unvisited bit][new cur node] = dp[mask][cur] + cost[cur][new cur]
 *    note: Using dp bitmask with dp[mask][cur] as min cost to visit all nodes in mask with last stop as node cur. Turn on bits which are unvisited and get min cost
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

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
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("lem3.INP", "r")) return;
    freopen("lem3.INP", "r", stdin);
    freopen("lem3.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 16;
ll INF;

int cost[N][N];
ll dp[1 << N][N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cin >> cost[i][j];
    }

    memset(dp,0x3f, sizeof(dp));
    INF = dp[0][0];

    for(int i = 0; i < n; i++) dp[1 << i][i] = 0;

    for(int mask = 0; mask < (1 << n); mask++){
        for(int cur = 0; cur < n; cur++){
            if(dp[mask][cur] == INF) continue;

            for(int v = 0; v < n; v++){
                if(mask >> v & 1) continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][cur] + cost[cur][v]);
            }
        }
    }

    ll ans = INF;
    int final_mask = (1 << n) - 1;
    for(int cur = 0; cur < n; cur++){
        ans = min(ans, dp[final_mask][cur]);
    }

    cout << ans;
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}