/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-03 13:47:52
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: MARATHON
 *    source: LCA2.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: Somehow if we have 2 same LCA then the odd one out will be the answer. Just imagine you pick the new root up and the tree will all fall down, then you consider all the case like the other node is above, below, between,...
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
    if(!fopen("MARATHON.INP", "r")) return;
    freopen("MARATHON.INP", "r", stdin);
    freopen("MARATHON.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 1e5+2;
vi adj[N];
int up[N][18];
int h[N];
int dis[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u){
    for(int v : adj[u]){
        if(v == up[u][0]) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;
        dis[v] = dis[u] + 1;

        for(int i = 1; i <= 17; i++){
            up[v][i] = up[up[v][i-1]][i-1];
        }

        dfs(v);
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

int getd(int a, int b){
    return dis[a] + dis[b] - 2*dis[lca(a,b)];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> q;   
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    } 

    dis[1] = 1;
    dfs(1);

    while(q--){
        int a,b,k;
        cin >> a >> b >> k;
        cout << (getd(a,b) == getd(a,k) + getd(k,b) ? 1 : 0) << '\n';
    }
}