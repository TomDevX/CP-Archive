/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-14 20:33:06
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Two Piece
 *    source: https://oj.vnoi.info/problem/euler_e
 *    submission: https://oj.vnoi.info/submission/12303918
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA, Tree Diameter
 *    complexity: O(n \log n)
 *    note: The furthest node that any node can go to is the two endpoints of the tree diameter, so we just need to lca on the path to 1 of 2 endpoints
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("euler_e.INP", "r")) return;
    freopen("euler_e.INP", "r", stdin);
    freopen("euler_e.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

vi adj[N];
int d1,d2;
int h[N], up[N][18], dis1[N], dis2[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;

        for(int k = 1; k <= 17; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v,u);
    }
}

void find_d1(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        dis1[v] = dis1[u] + 1;

        find_d1(v,u);
    }
}

void find_d2(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        dis2[v] = dis2[u] + 1;

        find_d2(v,u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dist = h[u] - h[v];
        for(int k = 17; k >= 0; k--){
            if(dist >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int k = 17; k >= 0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int get_path(int u, int v, int steps){
    int x = lca(u,v);

    int dist = h[u] - h[x];
    if(steps <= dist){
        for(int k = 17; k >= 0; k--){
            if(steps >> k & 1) u = up[u][k];
        }
        return u;
    }

    steps -= dist;
    steps = h[v] - h[x] - steps;
    for(int k = 17; k >= 0; k--){
        if(steps >> k & 1) v = up[v][k];
    }
    return v;
}

int solve(int u, int k){
    if(k > max(dis1[u], dis2[u])) return -1;

    if(k <= dis1[u]) return get_path(u,d1,k);
    return get_path(u,d2,k);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);
    for(int i = 1; i <= n; i++){
        if(h[i] > h[d1]){
            d1 = i;
        }
    }
    find_d1(d1,d1);
    for(int i = 1; i <= n; i++){
        if(dis1[i] > dis1[d2]){
            d2 = i;
        }
    }
    find_d2(d2,d2);

    int q;
    cin >> q;
    while(q--){
        int u,k;
        cin >> u >> k;

        cout << solve(u,k) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}
