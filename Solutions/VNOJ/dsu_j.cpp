/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-27 22:33:57
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: CÂY KHUNG NHỎ NHẤT
 *    source: https://oj.vnoi.info/problem/dsu_j
 *    submission: https://oj.vnoi.info/submission/12198747
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST
 *    complexity: O(n \log n)
 *    note: Typical MST
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
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
    if(!fopen("dsu_j.INP", "r")) return;
    freopen("dsu_j.INP", "r", stdin);
    freopen("dsu_j.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct Edge{
    int u,v;
    ll w;

    Edge(int _u = 0, int _v = 0, ll _w = 0) : u(_u), v(_v), w(_w) {};
    bool operator<(const Edge& o) const{
        return w < o.w;
    }
};

const int N = 2e5+2;
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

bool union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);
    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;

    return true;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,m;
    cin >> n >> m;

    vector<Edge> E(m+1);
    for(int i = 1; i <= m; i++) cin >> E[i].u >> E[i].v >> E[i].w;
    sort(all(E,1));

    ll ans = 0;
    for(int i = 1; i <= m; i++){
        if(union_set(E[i].u,E[i].v)) ans += E[i].w;
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}