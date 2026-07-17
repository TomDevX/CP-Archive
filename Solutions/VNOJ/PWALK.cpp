/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-03 14:02:46
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: PWALK
 *    source: https://oj.vnoi.info/problem/pwalk
 *    submission: https://oj.vnoi.info/submission/11787434
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n) 
 *    note: To calculate the distance on the tree, the path will go from root -> u -> lca(u,v) -> v so we have a formula: dis[root -> u] + dis[root -> v] - 2*dis[root -> lca(u,v)]
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

void setup(){
    if(!fopen("PWALK.INP", "r")) return;
    freopen("PWALK.INP", "r", stdin);
    freopen("PWALK.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 1e5+2;

vector<pii> adj[N];
int up[N][18];
int h[N];
int dist[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u){
    for(pii& v : adj[u]){
        if(v.fi == up[u][0]) continue;
        up[v.fi][0] = u;
        h[v.fi] = h[u] + 1;
        dist[v.fi] = dist[u] + v.se;

        for(int i = 1; i <= 17; i++){
            up[v.fi][i] = up[up[v.fi][i-1]][i-1];
        }
        dfs(v.fi);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int k = h[u] - h[v];
        for(int i = 17; i >= 0; i--){
            if(k >> i & 1) u = up[u][i];    
        }
    }
    if(u == v) return u;

    for(int i = 17; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    h[1] = 1;
    dfs(1);

    while(q--){
        int a,b;
        cin >> a >> b;
        cout << dist[a] + dist[b] - 2*dist[lca(a,b)] << '\n';
    }
}