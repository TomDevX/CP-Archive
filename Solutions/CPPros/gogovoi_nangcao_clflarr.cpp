/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-01 16:43:08
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: COLORFUL ARRAY
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_clflarr
 *    submission: https://oj.vnoi.info/submission/12221072
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(n \alpha (n))
 *    note: Instead of using segment tree, we can reverse the queries and apply the oldest color, dsu play a role as a next pointer for each elements
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <array>
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
    if(!fopen("gogovoi_nangcao_clflarr.INP", "r")) return;
    freopen("gogovoi_nangcao_clflarr.INP", "r", stdin);
    freopen("gogovoi_nangcao_clflarr.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int color[N], nx[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(nx + 1, nx + N, 1);
}

int find_next(int u){
    if(u == nx[u]) return u;
    return nx[u] = find_next(nx[u]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,q;
    cin >> n >> q;
    vector<array<int,4>> queries(q+1);
    for(int i = 1; i <= q; i++){
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
        queries[i][3] = i;
    }
    reverse(all(queries,1));
    
    for(int i = 1; i <= q; i++){
        int cur = find_next(queries[i][0]);
        while(cur <= queries[i][1]){
            color[cur] = queries[i][2];
            nx[cur] = find_next(cur + 1);
            cur = nx[cur];
        }
    }
    for(int i = 1; i <= n; i++) cout << color[i] << '\n';

    return NAH_I_WOULD_WIN;
}
