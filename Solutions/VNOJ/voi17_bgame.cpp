/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-11 17:06:01
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: VOI 17 Bài 3 - Trò chơi
 *    source: https://oj.vnoi.info/problem/voi17_bgame
 *    submission: https://oj.vnoi.info/submission/12281848
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST, LCA
 *    complexity: O(m \log m + m \log n)
 *    note: First to make a maximum f(x) as the problem requests we need the maximum possible edges first, so we make a MaxST (Maximum Spanning Tree). And then for each edge E which are not belong to MaxST, we check if it can make f(x) bigger, (because it will always make a cycle when adding the n_th edge into a tree), now we can use LCA to get min and max of that cycle (for example E is (u,v), so we check the cycle which contains u and v). And surprisingly, we do not need to check min value on that cycle because E must be the min (we made the maxST to we've already always took the max value for optimal big solution so E must have the lowest weight)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>
#include <numeric>

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
    if(!fopen("voi17_bgame.INP", "r")) return;
    freopen("voi17_bgame.INP", "r", stdin);
    freopen("voi17_bgame.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

struct Edge{
    int u,v,w,id;

    bool operator<(const Edge& o) const{
        return w > o.w;
    }
};

vpii adj[N];
bitset<N> vis;
int par[N], sz[N], up[N][17], upmax[N][17], h[N], id[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(sub(par,1,N-1),1);
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
    id[u] = id[pre];
    for(const pii& v : adj[u]){
        if(v.fi == pre) continue;

        h[v.fi] = h[u] + 1;
        up[v.fi][0] = u;
        upmax[v.fi][0] = v.se;

        for(int k = 1; k <= 16; k++){
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
        for(int k = 16; k >= 0; k--){
            if(dist >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int k = 16; k >= 0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int get_max(int u, int v){
    if(id[u] != id[v]) return -1e9;

    int x = lca(u,v);

    int dist = h[u] - h[x];
    int maxn = 0;
    for(int k = 16; k >= 0; k--){
        if(dist >> k & 1){
            maxn = max(maxn, upmax[u][k]);
            u = up[u][k];
        }
    }

    dist = h[v] - h[x];
    for(int k = 16; k >= 0; k--){
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

    sort(all(edges,1));

    for(int i = 1; i <= m; i++){
        if(unite(edges[i].u,edges[i].v)){
            adj[edges[i].u].eb(edges[i].v,edges[i].w);
            adj[edges[i].v].eb(edges[i].u,edges[i].w);
            vis[edges[i].id] = 1; 
        }
    }

    for(int i = 1; i <= n; i++){
        if(!id[i]) id[i] = i, dfs(i,i);
    }

    int ans = 0;
    for(int i = 1; i <= m; i++){
        if(!vis[edges[i].id]){
            ans = max(ans, get_max(edges[i].u,edges[i].v) + edges[i].w);
        }
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}