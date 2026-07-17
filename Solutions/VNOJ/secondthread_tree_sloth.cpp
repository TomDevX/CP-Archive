/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-10 07:41:13
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Sloth Naptime
 *    source: https://oj.vnoi.info/problem/secondthread_tree_sloth
 *    submission: https://oj.vnoi.info/submission/12273087
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: Let x = lca(a,b). Check if given power is enough to go from a to x, then from b to x
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
    if(!fopen("secondthread_tree_sloth.INP", "r")) return;
    freopen("secondthread_tree_sloth.INP", "r", stdin);
    freopen("secondthread_tree_sloth.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+5;

vi adj[N];
int up[N][19], h[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        up[v][0] = u;
        h[v] = h[u] + 1;

        for(int k = 1; k <= 18; k++) up[v][k] = up[up[v][k-1]][k-1];

        dfs(v,u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);
        int dis = h[u] - h[v];

        for(int k = 18; k >= 0; k--){
            if(dis >> k & 1) u = up[u][k];
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

int get_straight_dis(int a, int b){
    return h[a] - h[b];
}

int get_pos(int u, int dis){
    for(int k = 18; k >= 0; k--){
        if(dis >> k & 1) u = up[u][k];
    }
    return u;
}

int solve(int st, int ed, int dis){
    int x = lca(st,ed);

    int dis_st_x = get_straight_dis(st,x);
    if(dis <= dis_st_x){
        return get_pos(st,dis);
    }
    dis -= dis_st_x;

    int dis_ed_x = get_straight_dis(ed,x);
    if(dis >= dis_ed_x) return ed;

    return get_pos(ed,dis_ed_x-dis);
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

    dfs(1,0);

    int q;
    cin >> q;
    while(q--){
        int st,ed,dis;
        cin >> st >> ed >> dis;
        cout << solve(st,ed,dis) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}