/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-27 14:57:41
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Mọi người đang rời đi
 *    source: https://oj.vnoi.info/problem/dsu_f
 *    submission: https://oj.vnoi.info/submission/12194872
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(n \alpha(n))
 *    note: Each parent is itself until we delete it so just change the parent to the right position
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
    if(!fopen("dsu_f.INP", "r")) return;
    freopen("dsu_f.INP", "r", stdin);
    freopen("dsu_f.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;
int par[N];
int n,q;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    cin >> n >> q;

    while(q--){
        char type;
        int u;
        cin >> type >> u;
        
        if(type == '-'){
            par[u] = find_set(par[u]+1);
        }
        else{
            int ans = find_set(u);
            cout << (ans == n+1 ? -1 : ans) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}