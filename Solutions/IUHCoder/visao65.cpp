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

void dfs(int u, int lim){
    if(!adj[u].fi) return;
    dfs(adj[u].fi,lim);

    
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

    dfs(1,1e9);

    cout << ans;
}