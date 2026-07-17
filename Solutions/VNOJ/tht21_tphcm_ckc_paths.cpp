/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-10 18:59:29
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tin học trẻ 2021 TPHCM - Vòng Chung kết - Bảng C - Paths
 *    source: https://oj.vnoi.info/problem/tht21_tphcm_ckc_paths
 *    submission: https://oj.vnoi.info/submission/12278254
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST, LCA
 *    complexity: O(m \log m + m \log n)
 *    note: We notice that after building up a MST, if we need to keep one of those edges, the result will be the total of MST. If the problem gave another edge that isn't belong to MST, since we need to keep that so we need to remove the maximum edge in MST that is not needed, so how to know that it is not needed? When adding a new edge to a n-1 edge tree, there must be a cycle appear, and the edges which are in the cycles are not needed, and the cycle will range from the path from u to lca(u,v) and v to lca(u,v). So we use lca to determine the max edge in that cycle.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>
#include <bitset>

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
    if(!fopen("tht21_tphcm_ckc_paths.INP", "r")) return;
    freopen("tht21_tphcm_ckc_paths.INP", "r", stdin);
    freopen("tht21_tphcm_ckc_paths.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

vpii adj[N];
int par[N], sz[N], up[N][18], h[N], upmax[N][18];
bitset<N> vis;

struct Edge{
    int u,v,w,id;

    bool operator<(const Edge& o) const{
        return w < o.w;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(sub(par, 1, N-1), 1);
    fill(sub(sz,1,N-1),1);
}

int root(int u){
    if(u == par[u]) return u;
    return par[u] = root(par[u]);
}

bool unite(int a, int b){
    a = root(a), b = root(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;

    return true;
}

void dfs(int u, int pre){
    for(const pii &v : adj[u]){
        if(v.fi == pre) continue;

        up[v.fi][0] = u;
        h[v.fi] = h[u] + 1;
        upmax[v.fi][0] = v.se;

        for(int k = 1; k <= 17; k++){
            up[v.fi][k] = up[up[v.fi][k-1]][k-1];
            upmax[v.fi][k] = max(upmax[v.fi][k-1], upmax[up[v.fi][k-1]][k-1]);
        }

        dfs(v.fi,u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dist = h[u] - h[v];

        for(int k = 17; k >= 0; k--){
            if(dist >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int k = 17; k >= 0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int get_max(int u, int v){
    int x = lca(u,v);

    int maxn = 0;
    int dist = h[u] - h[x];
    for(int k = 17; k >= 0; k--){
        if(dist >> k & 1){
            maxn = max(maxn, upmax[u][k]);
            u = up[u][k];
        }
    }
    
    dist = h[v] - h[x];
    for(int k = 17; k >= 0; k--){
        if(dist >> k & 1){
            maxn = max(maxn, upmax[v][k]);
            v = up[v][k];
        }
    }

    return maxn;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,m;
    cin >> n >> m;

    vector<Edge> edges(m+1);

    for(int i = 1; i <= m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    vector<Edge> process = edges;

    sort(all(edges,1));

    ll tot = 0;
    for(int i = 1; i <= m; i++){
        if(unite(edges[i].u, edges[i].v)){
            adj[edges[i].u].eb(edges[i].v, edges[i].w);
            adj[edges[i].v].eb(edges[i].u, edges[i].w);
            tot += edges[i].w;
            vis[edges[i].id] = 1;
        }
    }

    dfs(1,0);

    for(int i = 1; i <= m; i++){
        if(vis[i]) cout << tot << '\n';
        else{
            cout << tot - get_max(process[i].u, process[i].v) + process[i].w << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}