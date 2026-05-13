/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-11 22:41:52
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: COCI 2019/2020 - Contest 5 - Putovanje
 *    source: https://oj.vnoi.info/problem/coci1920_r5_putovanje
 *    submission: https://oj.vnoi.info/submission/12285138
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA, Diff array on Tree
 *    complexity: O(n \log n)
 *    note: To know the price and to determine which package c1/c2 we will use, we need to know the visit time of each vertex. To know the visit time, we apply different array on tree and lca. If cnt[edge]*c1[edge] < c2[edge] -> use c1.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <queue>
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
    if(!fopen("coci1920_r5_putovanje.INP", "r")) return;
    freopen("coci1920_r5_putovanje.INP", "r", stdin);
    freopen("coci1920_r5_putovanje.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

vi adj[N];
ll c1[N], c2[N];
int up[N][18], h[N];
ll cnt[N];
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        up[v][0] = u;
        h[v] = h[u] + 1;

        for(int k = 1; k <= 17; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }

        dfs(v,u);
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

void process(int u, int v){
    int x = lca(u,v);

    cnt[u]++;
    cnt[v]++;

    cnt[x] -= 2;
}

void gang_up(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        gang_up(v,u);

        cnt[u] += cnt[v];
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;

    vpii edges(n);

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v >> c1[i] >> c2[i];
        edges[i] = {u,v};
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,0);

    for(int i = 2; i <= n; i++){
        process(i-1,i);
    }

    gang_up(1,0);

    ll ans = 0;
    for(int i = 1; i < n; i++){
        int u = edges[i].fi, v = edges[i].se;
        if(h[u] < h[v]) swap(u,v);

        if(c1[i]*cnt[u] < c2[i]){
            ans += c1[i]*cnt[u];
        }
        else ans += c2[i];
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}