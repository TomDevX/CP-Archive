/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-14 21:32:25
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Fast Lowest Common Ancestor
 *    source: https://oj.vnoi.info/problem/euler_g
 *    submission: https://oj.vnoi.info/submission/12304449
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour, LCA
 *    complexity: O(n \log n)
 *    note: Typical LCA with euler tour in O(1) query
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("euler_g.INP", "r")) return;
    freopen("euler_g.INP", "r", stdin);
    freopen("euler_g.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5, EN = 2*N;

vi adj[N];
int h[N];
int tour[EN], tin[EN];
int st[EN][18], lg[EN];
int timer = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tour[++timer] = u;
    tin[u] = timer;

    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        dfs(v,u);

        tour[++timer] = u;
    }
}

void build(){
    for(int i = 1; i <= timer; i++){
        st[i][0] = tour[i];
        if(i > 1) lg[i] = lg[i>>1] + 1;
    }

    for(int j = 1; j <= 17; j++){
        for(int i = 1; i + (1 << j) - 1 <= timer; i++){
            st[i][j] = (h[st[i][j-1]] < h[st[i + (1 << (j-1))][j-1]] ? st[i][j-1] : st[i + (1 << (j-1))][j-1]);
        }
    }
}

int get_min(int l, int r){
    int k = lg[r-l+1];
    return (h[st[l][k]] < h[st[r - (1 << k) + 1][k]] ? st[l][k] : st[r - (1 << k) + 1][k]);
}

int lca(int u, int v){
    if(tin[u] > tin[v]) swap(u,v);
    return get_min(tin[u], tin[v]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);
    build();

    int u,v,u_j,v_j,u_a,v_a;
    cin >> u >> v >> u_j >> v_j >> u_a >> v_a;

    int ans = 0;
    while(q--){
        ans ^= lca(u,v);
        u = (1LL*u*u_j + u_a) % n + 1;
        v = (1LL*v*v_j + v_a) % n + 1;
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}