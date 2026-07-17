/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-17 14:16:58
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: TREEDGE
 *    source: LCA4.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: The trick here is we get the farthest node (sort by the weight of edge, not the height) of each subtree u and subtree v on the query. Use euler tour and segment tree to get that one, then we also use LCA and get the max distance between u and v
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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
    if(!fopen("TREEDGE.INP", "r")) return;
    freopen("TREEDGE.INP", "r", stdin);
    freopen("TREEDGE.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 2e5+2;
struct node{
    int u;
    ll w;

    node(int _u = 0, ll _w = 0) : u(_u), w(_w) {};
};
vector<node> adj[N];
int tin[N], tout[N];
vi path = {0}, a;
int m = 0;
ll dis[N];
ll st[8*N];
int h[N];
int up[N][19];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u){
    tin[u] = ++m;
    path.eb(u);
    for(node v : adj[u]){
        if(tin[v.u]) continue;
        dis[v.u] = dis[u] + v.w;
        h[v.u] = h[u] + 1;

        up[v.u][0] = u;
        for(int i = 1; i <= 18; i++){
            up[v.u][i] = up[up[v.u][i-1]][i-1];
        }
        dfs(v.u);
    }
    tout[u] = ++m;
    path.eb(u);
}

void build(int id, int l, int r){
    if(l == r){
        st[id] = a[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    build(left,l,mid);
    build(left|1,mid+1,r);
    st[id] = max(st[left],st[left|1]);
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return -1e18;
    if(l >= u && r <= v){
        return st[id];
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return max(get(left,l,mid,u,v), get(left|1,mid+1,r,u,v));
}

int lca(int u, int v){
    if(u != v){
        if(h[u] < h[v]) swap(u,v);
        int k = h[u] - h[v];

        for(int j = 18; j >= 0; j--){
            if(k >> j & 1) u = up[u][j];
        }
    }
    if(u == v) return u;

    for(int j = 18; j >= 0; j--){
        if(up[u][j] != up[v][j]){
            u = up[u][j];
            v = up[v][j];
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
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    dfs(1);
    a = vi(m+1);
    for(int i = 1; i <= m; i++){
        a[i] = dis[path[i]];
    }
    build(1,1,m);

    while(q--){
        int u,v;
        ll x;
        cin >> u >> v >> x;

        ll dis_u = (tout[u] - tin[u] == 1 ? 0 : get(1,1,m,tin[u], tout[u]) - dis[u]);
        ll dis_v = (tout[v] - tin[v] == 1 ? 0 : get(1,1,m,tin[v], tout[v]) - dis[v]);

        cout << max(dis_u + dis_v + x, dis[u] + dis[v] - 2*dis[lca(u,v)]) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}