/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-20 16:21:32
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Kefa and Park
 *    source: https://codeforces.com/problemset/problem/580/C
 *    submission: https://codeforces.com/problemset/submission/580/367462297
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph, DFS/BFS
 *    complexity: O(n)
 *    note: Just do the normal dfs to count if the that cats reach the m consecutive because this is a tree
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <bitset>

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
    if(!fopen("580C.INP", "r")) return;
    freopen("580C.INP", "r", stdin);
    freopen("580C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m;
const int N = 1e5+2;
bitset<N> has_cat, vis;
int deg_out[N];
vi adj[N];
int ans = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int cnt){
    vis[u] = 1;
    for(int v : adj[u]){
        if(vis[v]) continue;
        deg_out[u]++;

        int nxt_cnt = (has_cat[v] ? cnt + 1 : 0);
        if(nxt_cnt <= m) dfs(v,nxt_cnt);
        else vis[v] = 1;
        
    }
    if(!deg_out[u]){
        ans += (cnt <= m);
    }
}  

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> m;
    for(int i = 1, x; i <= n; i++){
        cin >> x;
        has_cat[i] = x;
    }
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,has_cat[1]);

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}