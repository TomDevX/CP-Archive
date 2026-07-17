/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-14 22:47:40
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Promotion Counting
 *    source: https://usaco.org/index.php?page=viewproblem2&cpid=696
 *    submission: https://oj.vnoi.info/submission/12307332
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour, BIT
 *    complexity: O(n \log n)
 *    note: Just like the inversion counting problem but now it is on a tree so we need to turn the tree into the array with euler tour
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>

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
    if(!fopen("promote.in", "r")) return;
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

int val[N], queries[N], ans[N];
int bit[N];
vi adj[N];
int tour[N], tin[N], tout[N];
int timer = 0;
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tour[++timer] = u;
    tin[u] = timer;

    for(int v : adj[u]){
        if(v == pre) continue;

        dfs(v,u);
    }

    tout[u] = timer;
}

bool cmp(int a, int b){
    return val[a] > val[b];
}

void update(int pos, int val){
    for(; pos <= n; pos += pos&-pos) bit[pos] += val;
}

int get(int pos){
    int res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

int query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;

    for(int i = 1; i <= n; i++) cin >> val[i];

    for(int v = 2; v <= n; v++){
        int u;
        cin >> u;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    iota(sub(queries,1,n),1);
    sort(sub(queries,1,n), cmp);

    vi last;

    for(int i = 1; i <= n; i++){
        int u = queries[i];
        ans[u] = query(tin[u], tout[u]);
        update(tin[u],1);
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
    
    return NAH_I_WOULD_WIN;
}