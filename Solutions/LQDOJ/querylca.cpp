/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-13 07:17:10
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Truy vấn với LCA
 *    source: https://lqdoj.edu.vn/problem/querylca
 *    submission: https://lqdoj.edu.vn/submission/8591475
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log^2 n + q \log n) 
 *    note: Use sparse table to query lca on range
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
    if(!fopen("querylca.INP", "r")) return;
    freopen("querylca.INP", "r", stdin);
    freopen("querylca.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+5;

vi adj[N];
int up[N][19], h[N], st[N][19], lg[N];
int timer = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;

        for(int k = 1; k <= 18; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v,u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dist = h[u] - h[v];
        
        for(int k = 18; k >= 0; k--){
            if(dist >> k & 1){
                u = up[u][k];
            }
        }
    }
    if(u == v) return u;

    for(int k = 18; k >= 0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }

    return up[u][0];
}

int get(int l, int r){
    int k = lg[r-l+1];
    return lca(st[l][k], st[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;

    for(int i = 2; i <= n; i++) lg[i] = lg[i>>1] + 1;

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = 1; i <= n; i++) st[i][0] = i;

    for(int j = 1; j <= 18; j++){
        for(int i = 1; i + (1 << j) - 1 <= n; i++){
            st[i][j] = lca(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }

    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;

        cout << get(l,r) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}