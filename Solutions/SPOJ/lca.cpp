/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-03 12:22:20
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: LCA - Lowest Common Ancestor
 *    source: https://www.spoj.com/problems/LCA
 *    submission: 35721778
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n + q \alpha(n))
 *    note: We use Tarjan's Offline LCA (combination of DFS and DSU). First we need to arrange queries by nodes. There are 3 status of our nodes: current, in stack, visited. Now if we search top-down, and the desire node is visited, and our current node is connected to that node (in the query), so the lowest one that is in stack is our LCA -> we check that by union LCA each time we visited a child node from the parent nodes.
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
    if(!fopen("lca.INP", "r")) return;
    freopen("lca.INP", "r", stdin);
    freopen("lca.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1002;

vi adj[N];
bitset<N> vis;
vpii queries[N];
int par[N], sz[N], ancestor[N], ans[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dsu_init(int n){
    iota(par + 1, par + n + 1, 1);
    iota(ancestor + 1, ancestor + n + 1, 1);
    fill(sz + 1, sz + n + 1, 1);
}

void init(int n){
    dsu_init(n);
    vis.reset();
    for(int i = 1; i <= n; i++) adj[i].clear(), queries[i].clear();
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int a, int b, int anc){
    a = find_set(a), b = find_set(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    ancestor[a] = anc;
    par[b] = a;
}


void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;  
        dfs(v,u);
        union_set(u,v,u);
    }
    
    vis[u] = 1;
    for(const pii &p : queries[u]){
        if(vis[p.fi]) ans[p.se] = ancestor[find_set(p.fi)];
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    for(int test = 1; test <= tc; test++){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            int m;
            cin >> m;
            for(int j = 1; j <= m; j++){
                int x;
                cin >> x;
                adj[i].eb(x);
                adj[x].eb(i);
            }
        }
        
        int q;
        cin >> q;
        for(int i = 1; i <= q; i++){
            int u,v;
            cin >> u >> v;
            queries[u].eb(v,i);
            queries[v].eb(u,i);
        }
        
        dsu_init(n);
        dfs(1,-1);

        cout << "Case " << test << ":\n";
        for(int i = 1; i <= q; i++) cout << ans[i] << '\n';

        init(n);
    }
    
    return NAH_I_WOULD_WIN;
}