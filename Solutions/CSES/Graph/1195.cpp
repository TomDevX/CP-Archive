/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-23 09:00:55
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Flight Discount
 *    source: https://cses.fi/problemset/task/1195
 *    submission: https://cses.fi/problemset/result/16352463/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph, Dijkstra
 *    complexity: O((n+m) \log m)
 *    note: Use dis array as a dp array
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m;
const int N = 1e5+2;

struct node{
    int u;
    ll w;
    bool used;

    node(int _u, ll _w, bool _used = 0) : u(_u), w(_w), used(_used) {};
    bool operator<(const node& other) const{
        return w > other.w;
    }
};
vector<node> adj[N];

ll dis[N][2];

// ----------------------- [ FUNCTIONS ] -----------------------
void diks(int src){
    dis[src][0] = 0;
    priority_queue<node> pq;
    pq.push({src,0});

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();

        if(dis[u.u][u.used] < u.w) continue;

        for(node v : adj[u.u]){
            if(dis[v.u][u.used] > dis[u.u][u.used] + v.w){
                dis[v.u][u.used] = dis[u.u][u.used] + v.w;
                pq.push({v.u,dis[v.u][u.used],u.used});
            }

            if(u.used == 0){
                if(dis[v.u][1] > dis[u.u][0] + (v.w>>1)){
                    dis[v.u][1] = dis[u.u][0] + (v.w>>1);
                    pq.push({v.u,dis[v.u][1],1});
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

    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].eb(v,w);
    }

    diks(1);

    cout << dis[n][1];
}