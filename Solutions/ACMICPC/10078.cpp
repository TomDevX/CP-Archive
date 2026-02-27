/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-27 11:13:34
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Sightseeing
 *    source: https://www.acmicpc.net/problem/10078
 *    submission: https://www.acmicpc.net/source/103344425
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU, MST, Graph
 *    complexity: O((n + m) + m \log m + q + MAX_VAL)
 *    note: Our goal is to get the highest edge as possible, but if we use Dijkstra, it would be too harsh for the edges' priority queue. So that, we need to remove some unecessary edges, we use MST (Kruskal), but not minimum this time, we use maximum edges to maximize the answer. After that, we don't need to Dijkstra anymore because there is now 1 only way from any node u to node v on the "MST" - we use DFS/BFS. The hard thing here is the edges constraint is too large to we need to implement economically - I tried to use 1D arrays instead of vectors or 2D.
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
#include <algorithm>
#include <cstring>
#include <queue>
#include <type_traits>
#include <string>
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
using pii = pair<int,int>;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m,q;
const int N = 5e5+5;
const int VAL = 1e5+5;
const int M = 1e7+5;

struct node{
    int u,v;
    ll w;
    
    node(int _u = 0, int _v = 0, ll _w = 0) : u(_u), v(_v), w(_w) {};
};

node adj[M];
node sorted[M];
int cnt[VAL];
ll dis[N];
int par[N], sz[N];
int last[2*N], pre[2*N], to[2*N];
ll weight[2*N];
int edges = 1;
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    for(int i = 1; i <= n; i++) par[i] = i;
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

        for(int v_id = last[u]; v_id != 0; v_id = pre[v_id]){
            int v = to[v_id];
            if(!vis[v]){
                dis[v] = min(dis[u], weight[v_id]);
                qu.push(v);
                vis[v] = 1;
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
        cnt[adj[i].w]++;
    }

    int cur = 1;
    for(int i = VAL-5; i >= 0; i--){
        int tmp = cnt[i];
        cnt[i] = cur;
        cur += tmp;
    }

    for(int i = 1; i <= m; i++){
        sorted[cnt[adj[i].w]] = adj[i];
        cnt[adj[i].w]++;
    }

    for(int i = 1; i <= m; i++){
        if(union_set(sorted[i].u, sorted[i].v)){
            to[edges] = sorted[i].v;
            weight[edges] = sorted[i].w;
            pre[edges] = last[sorted[i].u];
            last[sorted[i].u] = edges;
            edges++;

            to[edges] = sorted[i].u;
            weight[edges] = sorted[i].w;
            pre[edges] = last[sorted[i].v];
            last[sorted[i].v] = edges;
            edges++;
        }
    }

    bfs(1);

    int x;
    while(q--){
        cin >> x;
        cout << dis[x] << '\n';
    }
}