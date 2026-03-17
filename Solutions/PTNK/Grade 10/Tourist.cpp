/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-17 13:37:52
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Tourist
 *    source: LCA4
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: Get dis from every distance between i and its multiple with LCA (because this is a tree)
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
    if(!fopen("Tourist.inp", "r")) return;
    freopen("Tourist.inp", "r", stdin);
    freopen("Tourist.out", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1e5+2;
vi adj[N];
bitset<N> vis;
int up[N][18];
int h[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u){
    vis[u] = 1;
    
    for(int v : adj[u]){
        if(vis[v]) continue;
        up[v][0] = u;
        for(int k = 1; k <= 17; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }
        h[v] = h[u] + 1;
        dfs(v);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int k = h[u] - h[v];
        for(int j = 17; j >= 0; j--){
            if(k >> j & 1) u = up[u][j];
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

int get_dis(int u, int v){
    return h[u] + h[v] - 2*h[lca(u,v)];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1);

    ll ans = 0;
    for(int i = 1; i < n; i++){
        for(int j = i*2; j <= n; j += i){
            ans += get_dis(i,j)+1;
        }
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}