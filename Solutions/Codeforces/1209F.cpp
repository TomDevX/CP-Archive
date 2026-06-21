/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-21 14:20:40
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Koala and Notebook
 *    source: https://codeforces.com/contest/1209/problem/F
 *    submission: https://codeforces.com/contest/1209/submission/379680947
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BFS, Graph
 *    complexity: O(n + m \log_10 m)
 *    note: We notice that this is a basic Lexicographical BFS traversal problem. We just need to group the one which have the best prefix into 1 group, and then iterate digits from 0 -> 9 and let them in the queue and update (and also lock because this is BFS not Dijkstra) their distance value.
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
    if(!fopen("1209F.INP", "r")) return;
    freopen("1209F.INP", "r", stdin);
    freopen("1209F.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7;
const int N = 1300005;

int n,m;
ll dis[N];
int virt;
int st[N];
int top_st = -1;
vi adj[N][10];
vi qu[N];
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void add(int u, int v, int w){
    while(w){
        st[++top_st] = w%10;
        w /= 10;
    }

    int cur = u;
    while(top_st > 0){
        adj[cur][st[top_st--]].eb(++virt);
        cur = virt;
    }

    adj[cur][st[top_st--]].eb(v);
}

void bfs(int src){
    int top = 0, tot = 0;
    qu[0] = {1};
    vis[1] = 1;

    while(top <= tot){
        vi cur = qu[top++];

        vi nxt[10];

        for(int d = 0; d <= 9; d++){
            for(int u : cur){
                for(int v : adj[u][d]){
                    if(vis[v]) continue;

                    vis[v] = 1;

                    dis[v] = (dis[u] * 10 + d)%MOD;

                    nxt[d].eb(v);
                }
            }
        }

        for(int d = 0; d <= 9; d++){
            if(!nxt[d].empty()) qu[++tot] = nxt[d];
        }
    }

}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> m;
    virt = n;

    for(int w = 1; w <= m; w++){
        int u,v;
        cin >> u >> v;
        add(u,v,w);
        add(v,u,w);
    }

    bfs(1);

    for(int u = 2; u <= n; u++){
        cout << dis[u] << '\n';
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