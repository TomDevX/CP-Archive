/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-14 09:14:28
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: VOI 25 Bài 1 - Người giao hàng
 *    source: https://oj.vnoi.info/problem/voi25_ship
 *    submission: https://oj.vnoi.info/submission/12115569
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA, Tree
 *    complexity: O(n \log n)
 *    note: We process the path as DP to get the most optimal result (because this is a tree so we can do DP easily). To get the max value from u,v on tree, we use up array to get the vertex id and max_value array to get the value of parent. Then use lca to track path
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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
    if(!fopen("SHIP.INP", "r")) return;
    freopen("SHIP.INP", "r", stdin);
    freopen("SHIP.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int val[N], up[N][19], max_val[N][19], h[N];
vi adj[N];
ll dp[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        max_val[v][0] = max(val[v], val[u]);
        up[v][0] = u;
        h[v] = h[u]+1;
        for(int i = 1; i <= 18; i++) up[v][i] = up[up[v][i-1]][i-1];
        for(int i = 1; i <= 18; i++) max_val[v][i] = max(max_val[v][i-1], max_val[up[v][i-1]][i-1]);
        dfs(v,u);
    }
} 

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dist = h[u] - h[v];
        for(int k = 18; k >= 0; k--){
            if(dist >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int i = 18; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int get_max(int u, int v){
    int k = h[v] - h[u];
    int res = val[v];
    for(int i = 18; i >= 0; i--){
        if(k >> i & 1){
            res = max(res, max_val[v][i]);
            v = up[v][i];
        }
    }
    return res;
}

int dismax(int u, int v){
    int mid = lca(u,v);
    return max(get_max(mid,u), get_max(mid,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> val[i];

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    max_val[1][0] = val[1];
    dfs(1,1);

    int k;
    cin >> k;
    vpii ways(k+1);
    for(int i = 1; i <= k; i++){
        cin >> ways[i].fi >> ways[i].se;
    }

    for(int i = k; i >= 1; i--){
        dp[ways[i].fi] = max(dp[ways[i].fi], dismax(ways[i].fi,ways[i].se) + dp[ways[i].se]);
    }

    cout << dp[1];

    return NAH_I_WOULD_WIN;
}