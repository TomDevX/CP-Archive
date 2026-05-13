/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-13 08:37:16
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Arcade Game
 *    source: https://oj.vnoi.info/problem/euler_c
 *    submission: https://oj.vnoi.info/submission/12292889
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour, LCA
 *    complexity: O(n \log n)
 *    note: Each edge will contribute its value to all the path in its subtree, so we just need to use euler tour + BIT + lca to find the path. Make the lower height node as the value of that edge
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

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
    if(!fopen("euler_c.INP", "r")) return;
    freopen("euler_c.INP", "r", stdin);
    freopen("euler_c.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

ll bit[N];
int tin[N], tout[N], h[N], up[N][18];
int timer = 0;
vi adj[N];

struct Edge{
    int u,v,w;

    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {};
};

Edge edges[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tin[u] = ++timer;
    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;

        for(int k = 1; k <= 17; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v,u);
    }
    tout[u] = timer;
}

void update(int pos, int val){
    for(; pos <= n; pos += pos&-pos) bit[pos] += val;
}

void update_range(int l, int r, int val){
    update(l,val);
    update(r+1,-val);
}

ll get(int pos){
    ll res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
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

ll get_path(int u, int v){
    int x = lca(u,v);

    return get(tin[u]) + get(tin[v]) - 2*get(tin[x]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v,w;
        cin >> u >> v >> w;

        edges[i] = {u,v,w};
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = 1; i < n; i++){
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if(h[u] < h[v]) swap(edges[i].u,edges[i].v), swap(u,v);

        update_range(tin[u], tout[u], w);
    }

    int q;
    cin >> q;
    int type;
    while(q--){
        cin >> type;
        if(type == 1){
            int id,w;
            cin >> id >> w;

            update_range(tin[edges[id].u], tout[edges[id].u], w-edges[id].w);
            edges[id].w = w;
        }
        else{
            int u,v;
            cin >> u >> v;
            cout << get_path(u,v) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}