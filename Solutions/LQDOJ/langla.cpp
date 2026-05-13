/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-09 22:44:57
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Làng Lá
 *    source: https://lqdoj.edu.vn/problem/langla
 *    submission: https://lqdoj.edu.vn/submission/8576865
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: Just draw on the paper and you'll see that the one that has the lowest height will be the best M
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

ll dis[N];
int up[N][19], h[N];
vpii adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre = -1){
    for(const pii& v : adj[u]){
        if(v.fi == pre) continue;

        up[v.fi][0] = u;
        h[v.fi] = h[u]+1;
        dis[v.fi] = dis[u] + v.se;
        for(int k = 1; k < 19; k++) up[v.fi][k] = up[up[v.fi][k-1]][k-1];

        dfs(v.fi,u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dist = h[u] - h[v];
        for(int k = 18; k >= 0; k--){
            if(dist >> k & 1) u = up[u][k];
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

ll get_dis_lca(int u, int v){
    return dis[u] - dis[v];
}

ll get_dis(int u, int v){
    return dis[u] + dis[v] - 2*dis[lca(u,v)];
}

int get_max_id(int a, int b, int c){
    int maxn = max({h[a],h[b],h[c]});
    if(maxn == h[a]) return 1;
    if(maxn == h[b]) return 2;
    return 3;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    dfs(1);

    cin >> q;
    while(q--){
        int a,b,c;
        cin >> a >> b >> c;

        int Lab = lca(a,b);
        int Lbc = lca(b,c);
        int Lac = lca(a,c);
        int maxn = get_max_id(Lab,Lbc,Lac);
        if(maxn == 1){
            cout << get_dis_lca(a,Lab) + get_dis_lca(b,Lab) + get_dis(c,Lab) << '\n';
        }
        else if(maxn == 2){
            cout << get_dis(a,Lbc) + get_dis_lca(b,Lbc) + get_dis_lca(c,Lbc) << '\n';
        }
        else{
            cout << get_dis_lca(a,Lac) + get_dis(b,Lac) + get_dis_lca(c,Lac) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}