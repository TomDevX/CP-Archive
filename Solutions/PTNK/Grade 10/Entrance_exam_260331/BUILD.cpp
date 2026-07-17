/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-31 15:27:01
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
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
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>
#include <queue>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
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
    if(!fopen("BUILD.INP", "r")) return;
    freopen("BUILD.INP", "r", stdin);
    freopen("BUILD.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
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
priority_queue<node> pq;
int n,m,k,l;

// ----------------------- [ FUNCTIONS ] -----------------------
void diks(int src){
    dis[src] = 0;
    pq.push({src,0});

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();

        if(u.w > dis[u.u]) continue;

        for(node v : adj[u.u]){
            if(dis[v.u] > dis[u.u] + u.w){
                dis[v.u] = dis[u.u] + u.w;
                pq.push({v.u, dis[v.u]});
            }
        }
    }
}

namespace sub1{
    bool check(){
        return k == 1;
    }
    void solve(){
        cin >> n >> m >> k >> l;
        
        for(int i = 1; i <= m; i++){
            int u,v;
            ll w;
            cin >> u >> v >> w;
            adj[u].eb(v,w);
            adj[v].eb(u,w);
        }
        
        diks(1);

        ll ans = dis[n];
        
        if(l >= 1){
            int u,v;
            ll w;
            cin >> u >> v >> w;
            adj[u].eb(v,w);
            memset(dis,0x3f,sizeof(dis));
            diks(1);
        }

        ans = min(ans, dis[n]);
        cout << (ans == dis[0] ? -1 : ans);
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(dis,0x3f,sizeof(dis));
    
    cin >> n >> m >> k >> l;
    if(sub1::check()) return sub1::solve(),0;

    for(int i = 1; i <= m; i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    vector<pair<int,node>> adds(k+1);
    for(int i = 1; i <= k; i++){
        cin >> adds[i].fi >> adds[i].se.u >> adds[i].se.w;
    }

    ll ans = 2e18;

    for(int mask = 0; mask < (1 << k); mask++){
        if(__builtin_popcount(mask) != l) continue;
        for(int j = 1; j <= k; j++){
            if(mask >> (j-1) & 1){
                adj[adds[j].fi].eb(adds[j].se.u, adds[j].se.w);
            }
        }

        diks(1);

        ans = min(ans, dis[n]);
        for(int i = 1; i <= n; i++) dis[i] = dis[0];

        for(int j = k; j >= 1; j--){
            if(mask >> (j-1) & 1){
                adj[adds[j].fi].pop_back();
            }
        }

        dbg(ans,1);
    }

    cout << (ans < 2e18 ? ans : -1);
    
    return NAH_I_WOULD_WIN;
}