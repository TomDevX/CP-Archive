/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-14 22:23:38
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Cow Land
 *    source: https://usaco.org/index.php?page=viewproblem2&cpid=921
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA, Euler Tour, BIT
 *    complexity: O(n \log n)
 *    note: For changing the value and calculating XOR sum, we need to do BIT on Euler Tour, but we need to calculate the shortest path between 2 nodes, not from the root, so we also need LCA
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
    if(!fopen("cowland.in", "r")) return;
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

int val[N];
vi adj[N];
int tour[N], tin[N], tout[N];
int up[N][17], h[N];
int bit[N];
int timer = 0;
int n,q;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tour[++timer] = u;
    tin[u] = timer;

    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;

        for(int k = 1; k <= 16; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v,u);
    }
    tout[u] = timer;
}

void update(int pos, int val){
    for(; pos <= timer; pos += pos&-pos) bit[pos] ^= val;
}

void update_range(int l, int r, int v){
    update(l,v);
    update(r+1,v);
}

int get(int pos){
    int res = 0;
    for(; pos; pos -= pos&-pos) res ^= bit[pos];
    return res;
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);
        
        int dist = h[u] - h[v];
        for(int k = 16; k>= 0; k--){
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

int ask(int u, int v){
    int x = lca(u,v);

    return get(tin[u]) ^ get(tin[v]) ^ val[lca(u,v)]; // they are all got XORed by the inclusion nodes (include lca), so we need to complement LCA's value back
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> val[i];

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = 1; i <= n; i++){
        update_range(tin[i], tout[i], val[i]);
    }

    int type;
    while(q--){
        cin >> type;
        if(type == 1){
            int id, v;
            cin >> id >> v;
            update_range(tin[id], tout[id], val[id]^v);
            val[id] = v;
        }
        else{
            int u,v;
            cin >> u >> v;
            cout << ask(u,v) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}