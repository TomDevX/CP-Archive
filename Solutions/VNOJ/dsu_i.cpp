/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-02 10:42:03
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bosses
 *    source: https://oj.vnoi.info/problem/dsu_i
 *    submission: https://oj.vnoi.info/submission/12225124
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(q \log n)
 *    note: Do an inclusion-exclusion on the dsu tree, just assume that the height is the value and we need to +1 each time
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
    if(!fopen("dsu_i.INP", "r")) return;
    freopen("dsu_i.INP", "r", stdin);
    freopen("dsu_i.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+2;
int par[N], sz[N], h[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
    fill(sz + 1, sz + N, 1);
}  

int find_set(int u){
    if(u == par[u]) return u;
    int root = find_set(par[u]);
    if(par[u] != root){
        h[u] += h[par[u]]; // add back if h[par[u]] have been changed from its original before when unioning
        par[u] = root; // make h (on DSU path compression, not actual h[]) = 1
    }
    return root;
}

void union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return;

    sz[b] += sz[a];
    par[a] = b; // can't use union by size because the problem states that b must be new root
    h[a] -= h[b]; // exlucsion for h[a], will be included again in the path compressing
    h[a] += 1; // add 1 value to its subtree

    return;
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
        else{
            int x;
            cin >> x;
            find_set(x); // path compressing
            cout << h[x] << '\n'; // dont need to + h[par[x]] because it is always 0 after path compression
        }
    }
    
    return NAH_I_WOULD_WIN;
}