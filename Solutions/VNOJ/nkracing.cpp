/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-06 16:30:39
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Vòng đua F1
 *    source: https://oj.vnoi.info/problem/nkracing
 *    submission: https://oj.vnoi.info/submission/12250760 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST
 *    complexity: O(n \log n)
 *    note: Because this is a cycle, so there will be some spare edges that are not needed to make a tree, so that is the number of cams (racetrack) we need to place. So which edge should we choose? Instead of choosing those edges directly, we can solve the complementary problem is that count the most expensive edges so that there only cheapest remains -> use maximum spanning tree
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
    if(!fopen("nkracing.INP", "r")) return;
    freopen("nkracing.INP", "r", stdin);
    freopen("nkracing.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int M = 1e5+2, N = 1e4+2;

struct Edge{
    int u,v,w;

    bool operator<(const Edge& o) const{
        return w > o.w;
    }
};

Edge E[M];
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
    fill(sz + 1, sz + N, 1);
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

bool unite(int a, int b){
    a = find_set(a), b = find_set(b);
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
    
    int n,m;
    cin >> n >> m;

    ll tot = 0, ans = 0;

    for(int i = 1; i <= m; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
        tot += E[i].w;
    }
    sort(E+1,E+m+1);
    
    for(int i = 1; i <= m; i++){
        if(unite(E[i].u,E[i].v)) ans += E[i].w;
    }

    cout << tot - ans;
    
    return NAH_I_WOULD_WIN;
}