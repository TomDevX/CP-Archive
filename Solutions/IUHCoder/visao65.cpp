/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-18 18:26:55
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Công ty đa cấp
 *    source: https://oj.iuhcoder.com/problem/visao65
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
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 2e5+2;
pii adj[N];
int h[N], sz[N];
int ans = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int u){
    sz[u] = 1;
    h[u] = 1;

    int v = adj[u].fi;

    if(!v) return;

    init(v);
    h[u] = h[v] + 1;
    sz[u] += sz[v];
    
    v = adj[u].se;
    if(!v) return;

    init(v);
    h[u] = max(h[u],h[v]+1);
    sz[u] += sz[v];
}

void cut(int u, int lim){
    if(lim + 1 == 0){
        ans += sz[adj[u].fi];
        ans += sz[adj[u].se];
        sz[u] -= sz[adj[u].fi] + sz[adj[u].se];
        h[u] = 1;
        return;
    }

    if(adj[u].fi){
        cut(adj[u].fi,lim-1);
        
        if(adj[u].se) cut(adj[u].se, lim - 1);
    }
    h[u] = max(h[adj[u].fi], h[adj[u].se]) + 1;
}

void solve(int u){
    if(adj[u].fi){
        solve(adj[u].fi);

        if(adj[u].se) solve(adj[u].se);
    }

    h[u] = max(h[adj[u].fi], h[adj[u].se]) + 1;
    
    int lim = min(h[adj[u].fi], h[adj[u].se]);
    
    cut(adj[u].fi,lim);
    cut(adj[u].se,lim);
    h[u] = max(h[adj[u].fi], h[adj[u].se]) + 1;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        if(adj[u].fi) adj[u].se = v;
        else adj[u].fi = v;
    }

    init(1);

    solve(1);

    cout << ans;
}