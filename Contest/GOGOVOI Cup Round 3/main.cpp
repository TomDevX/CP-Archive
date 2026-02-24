/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-24 00:13:23
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: High Score Dijkstra
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
#include <queue>
#include <bitset>
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
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2502;
int n,m;
struct node{
    int u;
    ll w;

    node(int _u = 0, ll _w = 0) : u(_u), w(_w) {};
    bool operator<(const node& other) const{
        return w > other.w;
    }
};
vector<node> adj[N], adj2[N];
ll dis[N];
int cnt[N];
bitset<N> vis1,vis2;

// ----------------------- [ FUNCTIONS ] -----------------------
void dijkstra(int src){
    dis[src] = 0;

    priority_queue<node> pq;
    pq.push({src,0});
    cnt[src] = 1;

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();
        
        if(u.w > dis[u.u]) continue;
        dbg(u.u,1);
        
        for(node v : adj[u.u]){
            if(!vis1[v.u] || !vis2[v.u]) continue;
            if(dis[v.u] > dis[u.u] + v.w){
                dis[v.u] = dis[u.u] + v.w;
                cnt[v.u]++;
                if(cnt[v.u] > n){
                    dis[n] = 1;
                    return;
                }
                pq.push({v.u,dis[v.u]});
            }
        }
    }
}

void dfs1(int u){
    vis1[u] = 1;
    
    for(node v : adj[u]){
        if(!vis1[v.u]) dfs1(v.u);
    }
}

void dfs2(int u){
    vis2[u] = 1;
    
    for(node v : adj2[u]){
        if(!vis2[v.u]) dfs2(v.u);
    }
}
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(dis,0x3f,sizeof(dis));
    
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        ll w;

        cin >> u >> v >> w;
        adj[u].eb(v,-w);
        adj2[v].eb(u,-w);
    }
    
    dfs1(1);
    dfs2(n);
    
    dijkstra(1);
    
    cout << -dis[n];
    
    // int maxn = 0;
    // for(int i = 1; i <= n; i++) maxn = max(maxn, cnt[i]);

    // cerr << '\n' << maxn;
}