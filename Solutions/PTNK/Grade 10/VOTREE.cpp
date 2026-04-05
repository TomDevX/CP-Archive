/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-24 13:49:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: VOTREE
 *    source: LCA5.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sparse table, LCA
 *    complexity: O(n \log n)
 *    note: LCA on range by using sparse table
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
    if(!fopen("VOTREE.INP", "r")) return;
    freopen("VOTREE.INP", "r", stdin);
    freopen("VOTREE.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 7e4+2;
int st[N][18], up[N][18], h[N], lg[N];
vi adj[N];
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int k = h[u] - h[v];

        for(int i = 17; i >= 0; i--){
            if(k >> i & 1) u = up[u][i];
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

void dfs(int u){
    vis[u] = 1;
    for(int v : adj[u]){
        if(vis[v]) continue;

        h[v] = h[u] + 1;

        up[v][0] = u;
        for(int k = 1; k <= 17; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v);
    }
}

int get(int l, int r){
    int k = lg[r-l+1];
    return lca(st[l][k], st[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    for(int i = 2; i <= n; i++) lg[i] = lg[i>>1] + 1;

    for(int i = 1; i <= n; i++) st[i][0] = i;
    dfs(1);

    for(int k = 1; k <= 17; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st[i][k] = lca(st[i][k-1], st[i + (1 << (k-1))][k-1]);
            dbg(st[i][k], make_pair(i,k));
        }
    }

    while(q--){
        int u,v;
        cin >> u >> v;

        cout << get(u,v) << '\n';
    }

    return NAH_I_WOULD_WIN;
}