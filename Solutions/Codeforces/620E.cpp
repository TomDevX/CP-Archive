/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-17 00:06:55
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: New Year Tree
 *    source: https://codeforces.com/problemset/problem/620/E
 *    submission: 
 *    status: WIP
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
    if(!fopen("620E.INP", "r")) return;
    freopen("620E.INP", "r", stdin);
    freopen("620E.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 4e5+5;

ll st[4*N], t[4*N];
int val[N];
vi adj[N];
int tour[N], tin[N], tout[N];
int timer = 0;

int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u ,int pre){
    tour[++timer] = val[u];
    tin[u] = timer;

    for(int v : adj[u]){
        if(v == pre) continue;

        dfs(v,u);
    }

    tout[u] = timer;
}

void build(int id, int l, int r){
    if(l == r){
        st[id] = (1 << tour[l]);
        return;
    }

    int mid = l+((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = st[lc] | st[lc|1];
}

void down(int id){
    int f = t[id];
    if(f == 0) return;

    t[id] = 0;

    int lc = id<<1;

    st[lc] = st[lc|1] = t[lc] = t[lc|1] = f;
}

void update(int id, int l, int r, int u, int v, int val){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id] = (1 << val);
        t[id] = (1 << val);

        return;
    }

    down(id);
    int mid = l + ((r-l)>>1);
    int lc = id<<1; 

    update(lc,l,mid,u,v,val);
    update(lc|1,mid+1,r,u,v,val);

    st[id] = st[lc] | st[lc|1];
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    down(id);
    int mid = l + ((r-l)>>1);
    int lc= id<<1;

    return get(lc,l,mid,u,v) | get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++){
        cin >> val[i];
    }

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);
    build(1,1,timer);

    int type;
    while(q--){
        cin >> type;
        if(type == 1){
            int u,c;
            cin >> u >> c;
            update(1,1,timer,tin[u], tout[u], c);
        }
        else{
            int u;
            cin >> u;

            cout << __builtin_popcountll(get(1,1,timer,tin[u], tout[u])) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}