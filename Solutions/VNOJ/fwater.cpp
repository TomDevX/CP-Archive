/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-06 18:14:03
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Tưới nước đồng cỏ
 *    source: https://oj.vnoi.info/problem/fwater
 *    submission: https://oj.vnoi.info/submission/12251173
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST
 *    complexity: O(n \log n)
 *    note: At first, you may approach the problem by building an initial MST, and choose the cheapest node to be the source, and then second source and check if the edges has too large price than the cost of that node, and start removing notes. That approach wouldn't help because this approach has a fixed MST at start and it can't be flexible after we make multi node as the water source. So we make a virtual source which can be understood as the first source, it connects to every node with the weight of w[i], and then we do MST on that.
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
    if(!fopen("fwater.INP", "r")) return;
    freopen("fwater.INP", "r", stdin);
    freopen("fwater.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 305, M = N*N;

struct Edge{
    int u,v,w;

    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {};
    bool operator<(const Edge& o) const{
        return w < o.w;
    }
};

Edge E[M];
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(sub(par,1,N-1),1);
    fill(sub(sz,1,N-1),1);
}

int root(int u){
    if(u == par[u]) return u;
    return par[u] = root(par[u]);
}

bool unite(int a, int b){
    a = root(a), b = root(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;

    return true;
}
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n;
    cin >> n;

    int m = 0;
    for(int i = 1, x; i <= n; i++){
        cin >> x;
        E[++m] = Edge(0,i,x);
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int x;
            cin >> x;
            if(j <= i) continue;
            E[++m] = Edge(i,j,x);
        }
    }
    sort(sub(E,1,m));

    ll ans = 0;
    for(int i = 1; i <= m; i++){
        if(unite(E[i].u, E[i].v)){
            ans += E[i].w;
            dbg(E[i].v,E[i].u);
        }
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}