/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-13 11:22:51
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Cau mày (cây màu)
 *    source: https://oj.vnoi.info/problem/euler_d
 *    submission: https://oj.vnoi.info/submission/12293568
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
    if(!fopen("euler_d.INP", "r")) return;
    freopen("euler_d.INP", "r", stdin);
    freopen("euler_d.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int n;
int bit[N];
int tour[N], tout[N];
int c[N], sorted[N], pos[N], nxt[N];
int ans[N];
int timer = 0;
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tour[++timer] = u;
    for(int v : adj[u]){
        if(v == pre) continue;
        dfs(v,u);
    }
    tout[u] = timer;
}

void update(int pos, int val){
    for(; pos <= timer; pos += pos&-pos) bit[pos] += val;
}

void update_range(int l, int r, int val){
    update(l,val);
    update(r+1,-val);
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
    for(int i = 1; i <= n; i++) cin >> c[i], sorted[i] = c[i];

    sort(sub(sorted,1,n));

    for(int i = 1; i <= n; i++){
        c[i] = lower_bound(sub(sorted,1,n), c[i]) - sorted;
    }

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = timer; i >= 1; i--){
        if(pos[c[tour[i]]]){
            nxt[i] = pos[c[tour[i]]];
        }
        else nxt[i] = n+1;
        pos[c[tour[i]]] = i;
    }

    for(int i = 1; i <= timer; i++){
        if(pos[c[tour[i]]] == i){
            update(i,1);
        }
    }

    for(int i = 1; i <= timer; i++){
        ans[tour[i]] = query(i, tout[tour[i]]);
        update(i,-1);
        
        if(nxt[i] <= n) update(nxt[i],1);
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
    
    return NAH_I_WOULD_WIN;
}