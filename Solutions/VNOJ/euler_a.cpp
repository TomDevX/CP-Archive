/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-12 20:06:13
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Subtree Queries
 *    source: https://oj.vnoi.info/problem/euler_a
 *    submission: https://oj.vnoi.info/submission/12289526
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour
 *    complexity: O(n \log n)
 *    note: Typical DFS Euler tour
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
    if(!fopen("euler_a.INP", "r")) return;
    freopen("euler_a.INP", "r", stdin);
    freopen("euler_a.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int val[N], tin[N], tout[N];
int n,q;
ll bit[N];
vi adj[N];
int num = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, int val){
    for(; pos <= n; pos += pos&-pos){
        bit[pos] += val;
    }
}

ll get(int pos){
    if(pos == 0) return 0;
    ll res  = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

ll query(int l, int r){
    return get(r) - get(l-1);
}

void dfs(int u, int pre){
    tin[u] = ++num;
    for(int v : adj[u]){
        if(v == pre) continue;

        dfs(v,u);
    }
    tout[u] = num;
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
    
    dfs(1,0);

    for(int i = 1; i <= n; i++){
        update(tin[i],val[i]);
    }

    int type;
    while(q--){
        cin>>type;
        if(type == 1){
            int pos ,x;
            cin >> pos >> x;

            update(tin[pos],x-val[pos]);
            val[pos] = x;
        }
        else{
            int x;
            cin >> x;
            cout << query(tin[x],tout[x]) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}