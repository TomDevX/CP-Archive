/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-26 19:33:11
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Disjoint Sets Union
 *    source: https://oj.vnoi.info/problem/dsu_a
 *    submission: https://oj.vnoi.info/submission/12190836
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(q \log n)
 *    note: Typical DSU template
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
    if(!fopen("dsu_a.INP", "r")) return;
    freopen("dsu_a.INP", "r", stdin);
    freopen("dsu_a.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    iota(par + 1, par + n + 1,1);
}

int find_set(int u){
    if(par[u] == u) return u;
    return par[u] = find_set(par[u]);
}

bool union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return true;

    if(sz[a] < sz[b]) swap(a,b);

    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;

    return false;
}

bool get(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return true;
    return false;
}
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    init(n);

    string type;
    int a,b;
    while(q--){
        cin >> type >> a >> b;
        if(type == "union") union_set(a,b);
        else cout << (get(a,b) ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}