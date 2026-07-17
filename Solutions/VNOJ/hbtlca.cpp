/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-12 00:22:49
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: dynamic LCA
 *    source: https://oj.vnoi.info/problem/hbtlca
 *    submission: https://oj.vnoi.info/submission/12285418
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA, Graph
 *    complexity: O(n \log n)
 *    note: When chaging the root X, the new LCA of u and v must be the meeting up point (three-way fork or median point). So to get that median point, we need to get the one that has the lowest height in lca(u,v), lca(u,X), lca(v,X). And there always 2 out of them has the same value (just draw down and you'll see all cases) so we just need to get the odd one out by using XOR (^)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

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
    if(!fopen("hbtlca.INP", "r")) return;
    freopen("hbtlca.INP", "r", stdin);
    freopen("hbtlca.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

vi adj[N];
int up[N][17], h[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u ,int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        up[v][0] = u;
        h[v] = h[u] + 1;
        for(int k = 1; k <= 16; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v,u);
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

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    while(cin >> n){
        if(n == 0) return 0;
        for(int i = 1; i < n; i++){
            int u,v;
            cin >> u >> v;
    
            adj[u].eb(v);
            adj[v].eb(u);
        }
    
        dfs(1,0);
    
        int q;
        cin >> q;
        char type;
    
        int x = 1;
    
        while(q--){
            cin >> type;
            if(type == '!'){
                cin >> x;
            }
            else{
                int u,v;
                cin >> u >> v;
                cout << (lca(u,v)^lca(u,x)^lca(v,x)) << '\n'; // 
            }
        }

        for(int i = 1; i <= n; i++) adj[i].clear();
        memset(up,0,sizeof(up));
        memset(h,0,sizeof(h));
    }
    
    
    return NAH_I_WOULD_WIN;
}