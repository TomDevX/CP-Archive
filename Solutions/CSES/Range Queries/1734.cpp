/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-15 18:43:16
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Distinct Values Queries
 *    source: https://cses.fi/problemset/task/1734
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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
    if(!fopen("1734.INP", "r")) return;
    freopen("1734.INP", "r", stdin);
    freopen("1734.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;

int pos[N], suff[N], a[N], f[N];

struct Query{
    int l,r;

    Query(int _l = 0, int _r = 0) : l(_l), r(_r) {};
    bool operator<(const Query& other){
        return l < other.l;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = n; i >= 1; i--){
        if(pos[a[i]] == 0) suff[i] = n+1;
        suff[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    vector<Query> queries(q+1);
    for(int i = 1; i <= q; i++) cin >> queries[i].l >> queries[i].r;

    sort(all(queries,1));

    for(int i = 1; i <= q; i++){

    }
    
    return NAH_I_WOULD_WIN;
}