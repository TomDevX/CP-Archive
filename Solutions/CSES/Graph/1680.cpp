/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-06 02:30:24
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Longest Flight Route
 *    source: https://cses.fi/problemset/task/1680
 *    submission: https://cses.fi/problemset/result/17445496/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Topo Sort, DP on DAG
 *    complexity: O(n)
 *    note: You can either DP on DAG (with some flag + initial add trick to dp[n]) or simply topo sort it and do DP normally
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("1680.INP", "r")) return;
    freopen("1680.INP", "r", stdin);
    freopen("1680.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

vi adj[N];
int dp[N];
int n,m;
bool met = false;

// ----------------------- [ FUNCTIONS ] -----------------------
int dfs(int u){
    if(u == n) met = true;
    if(dp[u] != -1) return dp[u];
    dp[u] = -2;

    for(int v : adj[u]){
        if(dfs(v) > 0) dp[u] = max(dp[u], dp[v] + 1);
    }
    return dp[u];
}

vi traceback(){
    vi trace;
    trace.eb(1);
    for(int cur = 1; cur != n;){
        for(int v : adj[cur]){
            if(dp[v] + 1 == dp[cur]){
                cur = v;
                trace.eb(v);
                break;
            }
        }
    }
    return trace;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
    }

    memset(dp,-1,sizeof(dp));
    dp[n] = 1;
    dfs(1);

    if(!met || dp[1] == 0){
        cout << "IMPOSSIBLE";
    }
    else{
        cout << dp[1] << '\n';
        vi trace = traceback();
        for(int u : trace) cout << u << ' ';
    }
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