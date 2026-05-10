/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-10 08:14:39
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Lubenica
 *    source: https://oj.vnoi.info/problem/lubenica
 *    submission: https://oj.vnoi.info/submission/12274687
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA
 *    complexity: O(n \log n)
 *    note: Just use LCA combine with binary lifting on max and min
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

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
    if(!fopen("lubenica.INP", "r")) return;
    freopen("lubenica.INP", "r", stdin);
    freopen("lubenica.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

int up[N][17], maxup[N][17], minup[N][17], h[N];
vpii adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    memset(minup,0x3f,sizeof(minup));
}

void dfs(int u, int pre){
    for(const pii &v : adj[u]){
        if(v.fi == pre) continue;

        up[v.fi][0] = u;
        maxup[v.fi][0] = v.se;
        minup[v.fi][0] = v.se;
        h[v.fi] = h[u] + 1;
        
        for(int k = 1; k <= 16; k++){
            up[v.fi][k] = up[up[v.fi][k-1]][k-1];
            maxup[v.fi][k] = max(maxup[v.fi][k-1], maxup[up[v.fi][k-1]][k-1]);
            minup[v.fi][k] = min(minup[v.fi][k-1], minup[up[v.fi][k-1]][k-1]);
        }

        dfs(v.fi,u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);
        
        int dist = h[u] - h[v];
        for(int k = 16; k >= 0; k--){
            if(dist >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int k = 16; k >= 0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int get_max(int a, int b){
    if(h[a] < h[b]) swap(a,b);

    int dist = h[a] - h[b];

    int ans = 0;
    for(int k = 16; k >= 0; k--){
        if(dist >> k & 1){
            ans = max(ans,maxup[a][k]);
            a = up[a][k];
        }
    }
    return ans;
}

int get_min(int a, int b){
    if(h[a] < h[b]) swap(a,b);

    int dist = h[a] - h[b];

    int ans = 2e9;
    for(int k = 16; k >= 0; k--){
        if(dist >> k & 1){
            ans = min(minup[a][k], ans);
            a = up[a][k];
        }
    }
    return ans;
}

pii solve(int u, int v){
    int x = lca(u,v);

    if(u == 1 && v == 2){
        cerr << minup[v][2] << '\n';
    }

    return {min(get_min(u,x),get_min(v,x)), max(get_max(u,x),get_max(v,x))};
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v,w;
        cin >> u >> v>> w;
        adj[u].eb(v,w);
        adj[v].eb(u,w);
    }

    dfs(1,0);

    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        pii ans = solve(u,v);
        cout << ans.fi << ' ' << ans.se << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}