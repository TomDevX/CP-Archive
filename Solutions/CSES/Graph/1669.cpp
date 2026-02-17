/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-17 23:31:56
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Round Trip
 *    source: https://cses.fi/problemset/task/1669
 *    submission: https://cses.fi/problemset/result/16296787/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph
 *    complexity: O(V+E) 
 *    note: We use DFS until we see a vertex that is already visited and trace through the trace array
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
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
const int N = 1e5+2;
vi adj[N];
bitset<N> vis;
int trace[N];
bool ok = false;
int st,ed;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    vis[u] = 1;

    for(int v : adj[u]){
        if(ok) return;
        if(v == pre) continue;
        if(vis[v]){
            ed = u;
            st = v;
            ok = true;
            return;
        }

        trace[v] = u;
        dfs(v,u);
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    
    for(int i = 1; i <= n; i++){
        if(!vis[i]) dfs(i,i);
    }

    if(!ok){
        cout << "IMPOSSIBLE";
        return 0;
    }

    int cur = ed;
    vi res;
    while(cur != st){
        res.eb(cur);
        cur = trace[cur];
    }
    res.eb(st);
    cout << sz(res)+1 << '\n';
    for(int i = sz(res)-1; i >= 0; i--){
        cout << res[i] << ' ';
    }
    cout << st;
}