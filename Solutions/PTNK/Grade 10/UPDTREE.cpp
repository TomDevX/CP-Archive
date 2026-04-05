/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-17 15:29:02
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: UPDTREE
 *    source: LCA4.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph
 *    complexity: O(n) 
 *    note: Just do like a diff array but with the order of a tree
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
    if(!fopen("UPDTREE.INP", "r")) return;
    freopen("UPDTREE.INP", "r", stdin);
    freopen("UPDTREE.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1e5+2;
ll D[N], A[N];
bitset<N> vis, has_end;
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u){
    vis[u] = 1;
    for(int v : adj[u]){
        if(vis[v]) continue;

        D[v] += D[u] - (has_end[u] ? A[u] : 0);
        dfs(v);
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }   

    int q;
    cin >> q;
    while(q--){
        int u,v;
        ll w;

        cin >> u >> v >> w;
        D[u] += w;
        A[v] += w;
        has_end[v] = 1;
    }

    dfs(1);

    for(int i = 1; i <= n; i++){
        cout << D[i] + a[i] << ' ';
    }
    
    return NAH_I_WOULD_WIN;
}