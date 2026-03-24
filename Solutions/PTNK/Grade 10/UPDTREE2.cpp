/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-24 14:31:58
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: UPDTREE2
 *    source: LCA5.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <bitset>

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
    if(!fopen("UPDTREE2.INP", "r")) return;
    freopen("UPDTREE2.INP", "r", stdin);
    freopen("UPDTREE2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int lg[N], h[N], up[N][18], D[N];
ll pref[N];
vi adj[N];
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u){
    vis[u] = 1;
    for(int v : adj[u]){
        if(vis[v]) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;
        for(int k = 1; k <= 17; k++) up[v][k] = up[up[v][k-1]][k-1];

        dfs(v);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);
        
        int dis = h[u] - h[v];
        for(int k = 17; k >= 0; k--) if(dis >> k & 1) u = up[u][k];
    }
    if(u == v) return u;

    for(int k = 17; k >= 0; k--){
        if(up[u][k] != up[v][k]) u = up[u][k], v = up[v][k];
    }
    return up[u][0];
}

int dist(int a, int b){
    return h[a] + h[b] - 2*h[lca(a,b)];
}

bool isIn(int a, int b, int mid){
    return dist(a,b) == dist(a,mid) + dist(mid,b);
}

bool cmp(int a, int b){
    return h[a] > h[b];
}

void remove_diff(int a, int b){
    D[a]--;
    D[b]--;
    D[lca(a,b)]+=2;
}

void add_diff(int a, int b){
    D[a]++;
    D[b]++;
    D[lca(a,b)]-=2;
}

void dfs_last(int u){
    vis[u] = 1;
    for(int v : adj[u]){
        if(vis[v]) continue;

        dfs_last(v);

        D[u] += D[v];
    }
}

void build_pref(int u, int pre){
    pref[u] = pref[pre] + D[u];
    for(int v : adj[u]){
        if(v != pre) build_pref(v,u);
    }
}

ll get_pref(int a, int b){
    return pref[a] + pref[b] - 2*pref[lca(a,b)];
}
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q,p;
    cin >> n >> q >> p;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    while(q--){
        int a,b,u,v;
        cin >> a >> b >> u >> v;

        vi w = {lca(a,u), lca(a,v), lca(b,u), lca(b,v)};
        vi can;
        for(int x : w){
            if(isIn(a,b,x) && isIn(u,v,x)) can.eb(x);
        }
        sort(all(can,0),cmp);
        filter(can,0);

        if(sz(can) > 1){
            remove_diff(can[0], can[1]);
        }

        add_diff(a,b);
    }

    vis.reset();
    dfs_last(1);
    build_pref(1,0);

    while(p--){
        int u,v;
        cin >> u >> v;
        cout << get_pref(u,v) << ' ';
    }
    
    return NAH_I_WOULD_WIN;
}