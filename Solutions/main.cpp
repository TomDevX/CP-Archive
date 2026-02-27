/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-26 15:45:13
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: TRAVEL
 *    source: BT_20260226.pdf
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
#include <queue>
#include <algorithm>
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
const int N = 5e6+2;

struct node{
    int u;
    ll w;

    node(int _u = 0, ll _w = 0) : u(_u), w(_w) {};
    bool operator<(const node& other) const{
        return w > other.w;
    }
};

vector<node> adj[N];
ll dis[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void diks(int src){
    priority_queue<node> pq;
    pq.push({src,(ll)2e18});
    dis[src] = 2e18;

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();

        if(dis[u.u] > u.w) continue;
        
        for(node v : adj[u.u]){ 
            // dbg(min(v.w,dis[u.u]),v.u);
            if(dis[v.u] < min(v.w,dis[u.u])){
                dis[v.u] = min(v.w,dis[u.u]);
                pq.push({v.u,dis[v.u]});
            }
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> m >> q;

    for(int i = 1; i <= m; i++){
        int u,v;
        ll w;

        cin >> u >> v >> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    diks(1);

    dis[0] = 0;
    int x;
    while(q--){
        cin >> x;
        cout << dis[x] << '\n';
    }
}