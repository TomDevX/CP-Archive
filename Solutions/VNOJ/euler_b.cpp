/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-12 21:01:01
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Path Queries
 *    source: https://oj.vnoi.info/problem/euler_b
 *    submission: https://oj.vnoi.info/submission/12290347
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour
 *    complexity: O(n \log n)
 *    note: Just update range and query point with fenwick tree on the euler tour and you'll get the path
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
    if(!fopen("euler_b.INP", "r")) return;
    freopen("euler_b.INP", "r", stdin);
    freopen("euler_b.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int val[N], tin[N], tout[N];
ll bit[N];
int ord = 0;
vi adj[N];
int n,q;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tin[u] = ++ord;
    for(int v : adj[u]){
        if(v == pre) continue;

        dfs(v,u);
    }
    tout[u] = ord;
}

void update(int pos, int val){
    for(; pos <= n; pos += pos&-pos) bit[pos] += val;
}

void update_range(int l, int r, int val){
    update(l,val);
    update(r+1,-val);
}

ll get(int pos){
    ll res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> val[i];

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = 1; i <= n; i++){
        update_range(tin[i], tout[i],val[i]);
    }

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int pos,x;
            cin >> pos >> x;
            update_range(tin[pos],tout[pos],x-val[pos]);
            val[pos] = x;
        }
        else{
            int x;
            cin >> x;
            cout << get(tin[x]) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}