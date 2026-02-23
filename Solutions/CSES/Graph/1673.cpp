/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-23 08:32:45
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: High Score
 *    source: https://cses.fi/problemset/task/1673
 *    submission: https://cses.fi/problemset/result/16352395/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph, Bellman Ford
 *    complexity: O(n \cdot m)
 *    note: Just normal bellman ford (I swapped the weight to its opposite value just for easier processing)
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
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
int n,m;
const int N = 2502;

vector<pair<int,ll>> adj1[N], adj2[N];
bitset<N> vis1,vis2,inqueue;
ll dis[N];
int cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs1(int src){
    vis1[src] = 1;

    for(pair<int,ll> p : adj1[src]){
        if(!vis1[p.fi]) dfs1(p.fi);
    }
}

void dfs2(int src){
    vis2[src] = 1;

    for(pair<int,ll> p : adj2[src]){
        if(!vis2[p.fi]) dfs2(p.fi);
    }
}

void bellman(int src){
    dis[src] = 0;
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(pair<int,ll> p : adj1[j]){
                if(dis[p.fi] > dis[j] + p.se){
                    dis[p.fi] = dis[j] + p.se;

                    if(i == n && vis1[p.fi] && vis2[p.fi]){ // must check if this vertex affect the way from 1 to n by checking if 1 to u and u to n is valid
                        dis[n] = 1;
                        return;
                    }
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
        adj1[u].eb(v,-w);
        adj2[v].eb(u,-w);
    }

    dfs1(1);
    dfs2(n);

    bellman(1);

    cout << -dis[n];
}