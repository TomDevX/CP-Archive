/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-01 20:10:58
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Tái cấu trúc công ty
 *    source: https://oj.vnoi.info/problem/dsu_h
 *    submission: https://oj.vnoi.info/submission/12221988
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(n)
 *    note: We make 2 DSU, 1 with group merge and 1 to represent the right next position that is the "leader" of his set, so for each query 2, we just need to merge those "leader"
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
    if(!fopen("dsu_h.INP", "r")) return;
    freopen("dsu_h.INP", "r", stdin);
    freopen("dsu_h.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int par[N], nx[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
    iota(nx + 1, nx + N, 1);
    fill(sz + 1, sz + N, 1);
}

int find_nx(int u){
    if(u == nx[u]) return u;
    return nx[u] = find_nx(nx[u]);
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int a, int b){
    a =  find_set(a), b = find_set(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,q;
    cin >> n >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int a,b;
            cin >> a >> b;
            union_set(a,b);
        }
        else if(type == 2){
            int l,r;
            cin >> l >> r;
            for(int i = find_nx(l); i < r; i = find_nx(i)){
                union_set(i, i+1);
                nx[i] = find_nx(i+1);
            }
        }
        else{
            int a,b;
            cin >> a >> b;
            cout << (find_set(a) == find_set(b) ? "YES" : "NO") << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}