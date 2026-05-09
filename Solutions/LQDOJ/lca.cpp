/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-09 18:20:43
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tổ Tiên Chung Gần Nhất
 *    source: https://lqdoj.edu.vn/problem/lca
 *    submission: https://lqdoj.edu.vn/submission/8575057
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n + q \alpha (n))
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
    if(!fopen("lca.INP", "r")) return;
    freopen("lca.INP", "r", stdin);
    freopen("lca.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1005, Q = 3005;

vpii queries[N];
int par[N], sz[N], ans[Q], ancestor[N];
bitset<N> vis;
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    iota(sub(par,1,n),1);
    iota(sub(ancestor,1,n),1);
    fill(sub(sz,1,n),1);
}

void rest(int n){
    for(int i = 1; i <= n; i++) queries[i].clear(), adj[i].clear();
    vis.reset();
}

int root(int u){
    if(u == par[u]) return u;
    return par[u] = root(par[u]);
}

void unite(int a, int b, int anc){
    a = root(a), b = root(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);
    par[b] = a;
    sz[a] += sz[b];
    ancestor[a] = anc;
}

void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;
        dfs(v,u);
        unite(u,v,u);
    }
    vis[u] = 1;
    for(const pii& p : queries[u]){
        int v = root(p.fi);
        if(vis[p.fi]) ans[p.se] = ancestor[v];
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
        init(n);
        for(int i = 1; i <= n; i++){
            int m;
            cin >> m;
            for(int j = 1; j <= m; j++){
                int v;
                cin >> v;
                adj[i].eb(v);
                adj[v].eb(i);
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

        dfs(1,0);

        cout << "Case " << test << ":\n";

        for(int i = 1; i <= q; i++){
            cout << ans[i] << '\n';
        }
        rest(n);
    }
    
    return NAH_I_WOULD_WIN;
}