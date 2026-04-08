/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-08 09:42:44
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Subarray Sum Queries II
 *    source: https://cses.fi/problemset/task/3226
 *    submission: https://cses.fi/problemset/result/16838741/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree
 *    complexity: O(n \log n)
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
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
    if(!fopen("3226.INP", "r")) return;
    freopen("3226.INP", "r", stdin);
    freopen("3226.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 5e4+2;
int a[N];

struct node{
    int sum,pref,suff,best;

    node(int _sum = 0, int _pref = 0, int _suff = 0, int _best = 0) : sum(_sum), pref(_pref), suff(_suff), best(_best) {};
    node operator+(const node& other){
        int sumres = sum  + other.sum;
        int prefres = max({pref, sum + other.pref,0});
        int suffres = max({0,other.suff, other.sum + suff});
        int bestres = max({best, other.best, suff + other.pref,0});
        return node(sumres,prefres,suffres,bestres);
    }
};

node st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        int x = max(a[l],0);
        st[id] = node(a[l], x, x, x);
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = st[lc] + st[lc|1];
}

node get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return node(0,-1e9,-1e9,-1e9);
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return get(lc,l,mid,u,v) + get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1,1,n);

    while(q--){
        int l,r;
        cin >> l >> r;
        cout << get(1,1,n,l,r).best << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}