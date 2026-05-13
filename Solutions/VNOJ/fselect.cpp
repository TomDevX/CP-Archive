/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-10 00:04:58
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Làm quen bạn mới
 *    source: https://oj.vnoi.info/problem/fselect
 *    submission: https://oj.vnoi.info/submission/12272471
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: Just like the finding the diameter of the graph problem but this time is on certain verticals and on tree so we can use lca instead of dfs
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
    if(!fopen("fselect.INP", "r")) return;
    freopen("fselect.INP", "r", stdin);
    freopen("fselect.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

vi teams[N>>1], adj[N];
int up[N][18], h[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;
        for(int k = 1; k < 18; k++){
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

int get_dis(int u, int v){
    return h[u] + h[v] - 2*h[lca(u,v)];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;
    int root = 0;
    for(int i = 1; i <= n; i++){
        int team,v;
        cin >> team >> v;
        teams[team].eb(i);
        if(v == 0) root = i;
        else{
            adj[i].eb(v);
            adj[v].eb(i);
        }
    }

    dfs(root,0);

    for(int i = 1; i <= k; i++){
        int dist = 0, pos = 0;
        int u = teams[i][0];
        for(int j = 1; j < sz(teams[i]); j++){
            int cur_dist = get_dis(u, teams[i][j]);
            if(cur_dist > dist){
                dist = cur_dist;
                pos = j;
            }
        }

        u = teams[i][pos];
        for(int j = 0; j < sz(teams[i]); j++){
            if(j == pos) continue;
            dist = max(dist, get_dis(u,teams[i][j]));
        }

        cout << dist << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}