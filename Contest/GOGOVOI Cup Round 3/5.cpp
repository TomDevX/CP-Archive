/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-05 20:29:12
 *    country: Vietnam - VNM
 *    title: 
 *    source: 
 *    submission: 
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
#include <algorithm>
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
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5, M = 4e5+5;
int n,m;
ll c;
struct node{
    int u;
    ll w;

    node(int _u, ll _w = 0) : u(_u), w(_w) {};
    bool operator<(const node& other) const{
        return w > other.w;
    }
};
int b[N],d[N],e[N];
vector<node> adj[M];
ll dis[M];
priority_queue<node> pq;

// ----------------------- [ FUNCTIONS ] -----------------------
void diks(int src){
    dis[src] = 0;
    pq.push({src,0});

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();

        if(u.w > dis[u.u]) continue;

        // noi den b
        int tmp = n + b[u.u] + 1;
        if(u.u <= n && dis[tmp] > u.w + c){
            dis[tmp] = u.w + c;
            pq.push({tmp,dis[tmp]});
        }

        // di den i ke & tu b noi di khap noi
        for(node v : adj[u.u]){
            if(dis[v.u] > u.w + v.w){
                dis[v.u] = u.w + v.w;
                pq.push({v.u,dis[v.u]});
            }
        }

        // ban ten lua
        if(u.u <= n){
            for(int v = max(1,u.u-d[u.u]); v <= min(n,u.u+d[u.u]); v++){
                if(dis[v] > u.w + e[u.u]){
                    dis[v] = u.w + e[u.u];
                    pq.push({v,dis[v]});
                }
            }
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(dis,0x3f,sizeof(dis));

    cin >> n >> m >> c;
    for(int i = 1; i <= m; i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    for(int i = 1; i <= n; i++){
        cin >> b[i] >> d[i] >> e[i];
        adj[n+b[i]+1].eb(i);
    }

    diks(n);

    for(int i = 1; i <= n; i++) cout << (dis[i] == dis[0] ? -1 : dis[i]) << ' ';
}