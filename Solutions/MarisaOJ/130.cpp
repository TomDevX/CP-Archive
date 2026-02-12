/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-12 13:50:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: DSU
 *    source: https://marisaoj.com/problem/130
 *    submission: https://marisaoj.com/submission/1081451
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(n + q \cdot \alpha{n}) 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int par[N], sz[N];
int n,q;

// ----------------------- [ FUNCTIONS ] -----------------------
int find_set(int u){
    if(par[u] == u) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);

    par[b] = a;
    if(sz[a] == sz[b]) sz[a]++;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> q;
    for(int i = 1; i <= n; i++) par[i] = i;

    while(q--){
        int type,u,v;
        cin >> type >> u >> v;
        if(type == 1){
            union_set(u,v);
        }
        else{
            cout << (find_set(u) == find_set(v) ? "YES" : "NO") << '\n';
        }
    }
}