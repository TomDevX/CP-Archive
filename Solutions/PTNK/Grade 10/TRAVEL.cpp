/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-27 11:13:34
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: TRAVEL
 *    source: BT_20260226
 *    submission: TRAVEL_submission.log
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU, MST, Graph
 *    complexity: O(n + m \log m + q)
 *    note: Our goal is to get the highest edge as possible, but if we use Dijkstra, it would be too harsh for the edges' priority queue. So that, we need to remove some unecessary edges, we use MST (Kruskal), but not minimum this time, we use maximum edges to maximize the answer. After that, we don't need to Dijkstra anymore because there is now 1 only way from any node u to node v on the "MST" - we use DFS/BFS. The hard thing here is the edges constraint is too large to we need to implement economically.
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
#include <algorithm>
#include <cstring>
#include <queue>
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
    if(!fopen("TRAVEL.INP", "r")) return;
    freopen("TRAVEL.INP", "r", stdin);
    freopen("TRAVEL.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m,q;
const int N = 5e5+5;
const int M = 1e7+5;

struct node{
    int u,v;
    ll w;
    
    node(int _u = 0, int _v = 0, ll _w = 0) : u(_u), v(_v), w(_w) {};
};

node adj[M];
ll dis[N];
int par[N], sz[N];
vector<pair<int,ll>> E[N];
int edges = 1;
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    for(int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;
}

int find_set(int u){
    if(par[u] == u) return u;
    return par[u] = find_set(par[u]);
}

bool union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);

    par[b] = a;
    if(sz[a] == sz[b]) sz[a]++;

    return true;
}

void bfs(int src){  
    vis[src] = 1;
    
    queue<int> qu;
    qu.push(src);

    while(!qu.empty()){
        int u = qu.front();
        qu.pop();

        for(pair<int,ll> &v : E[u]){
            if(!vis[v.fi]){
                dis[v.fi] = min(dis[u],v.se);
                qu.push(v.fi);
                vis[v.fi] = 1;
            }
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(dis,0x3f,sizeof(dis));
    
    cin >> n >> m >> q;
    init();
    for(int i = 1; i <= m; i++){
        cin >> adj[i].u >> adj[i].v >> adj[i].w;
    }

    sort(adj+1, adj+m+1, [](const node& a, const node& b){return a.w > b.w;}); // non-increase

    for(int i = 1; i <= m; i++){ // MST
        if(union_set(adj[i].u, adj[i].v)){
            E[adj[i].u].eb(adj[i].v, adj[i].w);
            E[adj[i].v].eb(adj[i].u, adj[i].w);
        }
    }

    bfs(1);

    int x;
    while(q--){
        cin >> x;
        cout << dis[x] << '\n';
    }
}