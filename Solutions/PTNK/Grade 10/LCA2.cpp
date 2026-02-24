/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-24 14:32:01
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: LCA2
 *    source: LCA1.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: 
 *    note: 
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
    if(!fopen("LCA2.INP", "r")) return;
    freopen("LCA2.INP", "r", stdin);
    freopen("LCA2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,k;
const int N = 1e5+2;
int logg[N];
vi adj[N];
int up[N][19];
int h[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    logg[0] = logg[1] = 0;
    for(int i = 2; i <= n; i++){
        logg[i] = logg[i>>1] + 1;
    }
}

void dfs(int u){
    for(int v : adj[u]){
        if(v == up[u][0]) continue;
        h[v] = h[u] + 1;
        up[v][0] = u;

        for(int j = 1; j <= 17; j++){
            up[v][j] = up[up[v][j-1]][j-1];
        }
        dfs(v);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dis = h[u] - h[v];
        for(int j = 17; j >= 0; j--){
            if(dis >> j & 1) u = up[u][j];
        }
    }
    if(u == v) return u;

    for(int j = 17; j >= 0; j--){
        if(up[u][j] != up[v][j]) u = up[u][j], v = up[v][j];
    }
    return up[u][0];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();

    cin >> n;

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1);

    int q;
    cin >> q;
    while(q--){
        int a,b,r;
        cin >> a >> b >> r;
        cout << (lca(a,b)^lca(a,r)^lca(b,r)) << '\n';
    }
}