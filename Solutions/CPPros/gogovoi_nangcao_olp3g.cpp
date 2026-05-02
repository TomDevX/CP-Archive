/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-30 16:52:22
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Đặc trưng của cây
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_olp3g
 *    submission: https://oj.vnoi.info/submission/12215972
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(n \log n + n + m)
 *    note: Notice that sum(i: 1 -> n){sum(j: 1 -> n){max(i,j) - min(i,j)}} = sum(i: 1 -> n){sum(j: 1 -> n){max(i,j)}} - sum(i: 1 -> n){sum(j: 1 -> n){min(i,j)}}. Now we have 2 separate problems. For the max problem, We sort w[i] increasing. Now imagine that we are in a graph, a union of nodes are nodes that are connected together and there will be a max value in that group. For example, we are processing node X, which has the current highest value so far, now X is in union A, and WXalso connect to an lower value node Y from union B, since Y is in union B, Y also connects to all nodes in B, so when we connect X to Y, all nodes in B must go through X, and since X has current the highest value, our total cost to go from a node from A to B (or B to A) is size[A]*size[B]*w[X]. From this example, we continue doing it with the higher values ahead. To manage the unions, we use DSU. And then we do the same with sum of mins
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>
#include <numeric>
#include <bitset>

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
    if(!fopen("gogovoi_nangcao_olp3g.INP", "r")) return;
    freopen("gogovoi_nangcao_olp3g.INP", "r", stdin);
    freopen("gogovoi_nangcao_olp3g.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1e6+2;

int w[N], nodes[N], par[N], sz[N];
bitset<N> vis;
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + n + 1, 1);
    fill(sz + 1, sz + n + 1, 1);
    vis.reset();
}

inline int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

inline ll union_set_max(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b || !vis[b]) return 0; // a only connects to node which has higher value

    ll res = 1LL * sz[a] * sz[b];
    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;

    return res;
}

inline ll union_set_min(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b || !vis[b]) return 0; // a only connects to node which has lower value

    ll res = 1LL * sz[a] * sz[b];
    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;

    return res;
}

ll solve_max(){
    ll res = 0;
    for(int i = 1; i <= n; i++){
        int u = nodes[i];
        vis[u] = 1;
        for(int v : adj[u]){
            res += union_set_max(u,v)*w[u];
        }
    }
    return res;
}

ll solve_min(){
    ll res = 0;
    for(int i = 1; i <= n; i++){
        int u = nodes[i];
        vis[u] = 1;
        for(int v : adj[u]){
            res += union_set_min(u,v)*w[u];
        }
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> w[i];

    iota(nodes + 1, nodes + n + 1, 1);
    
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    
    sort(nodes + 1, nodes + n + 1, [](const int id1, const int id2) noexcept -> bool {
        return w[id1] < w[id2];
    });
    
    init();
    ll ans = solve_max();
    
    reverse(nodes + 1, nodes + n + 1);
    init();

    cout << ans - solve_min();
    
    return NAH_I_WOULD_WIN;
}