/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-06 02:59:41
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Game Routes
 *    source: https://cses.fi/problemset/task/1681
 *    submission: https://cses.fi/problemset/result/17445572/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Topo Sort, DP on DAG
 *    complexity: O(n)
 *    note: You can either dp on dag with dp[n] = 1 trick and other = -1 or topo sort them and dp normally
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
    if(!fopen("1681.INP", "r")) return;
    freopen("1681.INP", "r", stdin);
    freopen("1681.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;
const ll MOD = 1e9+7;

vi adj[N];
ll dp[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int dfs(int u){
    if(dp[u] != -1) return dp[u];
    dp[u] = -2;

    for(int v : adj[u]){
        if(dfs(v) > 0){
            dp[u] = max(dp[u], 0LL);
            dp[u] = (dp[u] + dp[v]) % MOD;
        }
    }

    return dp[u];
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
    }

    memset(dp,-1,sizeof(dp));

    dp[n] = 1;
    dfs(1);

    cout << max(0LL,dp[1]);
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