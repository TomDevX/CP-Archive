/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-08 20:11:56
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Edges in MST
 *    source: https://codeforces.com/problemset/problem/160/D
 *    submission: https://codeforces.com/problemset/submission/160/373918629
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST
 *    complexity: O(E \log E + E \alpha(N))
 *    note: For the not included and at least 1 MST is easy because you just need check if the edge is still available to unite (root(u) != root(v)) after merging the lower weights. For an edge to be in any MST, it must be a bridge in our graph. So assume that we combined and processed bridge for edges has lower w. We then processing tarjan to find bridge on that graph with each connected component as 1 node, and we check the recently added edges.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>
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
    if(!fopen("160D.INP", "r")) return;
    freopen("160D.INP", "r", stdin);
    freopen("160D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2, M = min(1LL*N, 1LL*N*((N-1)>>1LL));

struct Edge{
    int u,v,w;
    int id;

    Edge(int _u = 0, int _v = 0, int _w = 0, int _id = 0) : u(_u), v(_v), w(_w), id(_id) {};
    bool operator<(const Edge& o) const{
        return w < o.w;
    }
};

int cnt = 0;
int ans[M], num[N], low[N], par[N], sz[N];
vector<Edge> adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(sub(par,1,N-1),1);
    fill(sub(sz,1,N-1),1);
}

int root(int u){
    if(u == par[u]) return u;
    return par[u] = root(par[u]);
}

void unite(int a, int b){
    a = root(a), b = root(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;
}

void tarjan(int u, int id){
    num[u] = low[u] = ++cnt;

    for(const Edge &v : adj[u]){
        if(id == v.id) continue;
        if(num[v.v]){
            low[u] = min(low[u], num[v.v]);
            continue;
        }
        
        tarjan(v.v,v.id);
        low[u] = min(low[u], low[v.v]);

        if(num[v.v] == low[v.v]) ans[v.id] = 3;
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,m;
    cin >> n >> m;
    
    vector<Edge> edges(m+1);
    for(int i = 1; i <= m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }
    sort(all(edges,1));

    for(int i = 1, j = 2; i <= m; i = j){
        while(j <= m && edges[j].w == edges[i].w) j++;

        vi active;

        for(int k = i; k < j; k++){
            Edge &E = edges[k];
            int u = root(E.u), v = root(E.v), w = E.w, id = E.id;
            if(u != v){
                ans[id] = 1;
                adj[u].eb(0,v,w,id);
                adj[v].eb(0,u,w,id);
                active.eb(u);
                active.eb(v);
            }
        }

        for(int u : active){
            if(!num[u]) tarjan(u,-1);
        }

        for(int k = i; k < j; k++){
            int u = root(edges[k].u), v = root(edges[k].v);
            adj[u].clear();
            adj[v].clear();
            num[u] = num[v] = low[u] = low[v] = 0;
            unite(u,v);
        }
    }

    for(int i = 1; i <= m; i++){
        if(ans[i] == 0){
            cout << "none\n";
        }
        else if(ans[i] == 1){
            cout << "at least one\n";
        }
        else{
            cout << "any\n";
        }
    }
    
    return NAH_I_WOULD_WIN;
}