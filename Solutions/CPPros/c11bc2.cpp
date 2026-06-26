/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-26 23:48:50
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Robin
 *    source: https://oj.vnoi.info/problem/c11bc2
 *    submission: https://oj.vnoi.info/submission/12579540
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Tree, BFS, DFS
 *    complexity: O(n + q)
 *    metacognition: Thought of using LCA and a second array to query if there's an edge of 2 >< AC fast but still kinda complex -> Use normal DFS/BFS, we only pass through edges with k = 1, and mark them in components (id), then if id[u] == id[v] => they didn't go through any edge 2 | id[u] != id[v] => need to go through at least 1 edge 2
 *    note: Use normal DFS/BFS. Make components (id) but exclude edges with k = 2. If id[u] == id[v] => They're same component and didn't go through any edge k = 2, otherwise id[u] != id[v] => must have been go through at lease 1 edge = 2
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("c11bc2.INP", "r")) return;
    freopen("c11bc2.INP", "r", stdin);
    freopen("c11bc2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+1, LOG = 17;

int n,q;

vector<pair<int,bool>> adj[N];
int id[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int comp){
    id[u] = comp;
    for(pair<int,bool> &v : adj[u]){
        if(id[v.fi] || v.se) continue;

        id[v.fi] = comp;
        dfs(v.fi,comp);
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> q;

    for(int u = 2; u <= n; u++){
        int v,k;
        cin >> v >> k;
        adj[u].eb(v,k-1);
        adj[v].eb(u,k-1);
    }

    for(int i = 1; i <= n; i++){
        if(!id[i]) dfs(i,i);
    }

    while(q--){
        int u,v;
        cin >> u >> v;
        cout << (id[u] == id[v] ? "NO" : "YES") << '\n';
    }
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}