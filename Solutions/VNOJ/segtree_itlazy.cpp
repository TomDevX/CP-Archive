/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-28 20:36:40
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Educational Segment Tree Contest - ITLAZY
 *    source: https://oj.vnoi.info/problem/segtree_itlazy
 *    submission: https://oj.vnoi.info/submission/11975322
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree
 *    complexity: O(n \log n)
 *    note: Typical lazy segment tree
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
    if(!fopen("segtree_itlazy.INP", "r")) return;
    freopen("segtree_itlazy.INP", "r", stdin);
    freopen("segtree_itlazy.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int a[N];
ll st[4*N], t[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id] = a[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    build(left,l,mid);
    build(left|1,mid+1,r);
    st[id] = max(st[left],st[left|1]);
}

void down(int id){
    if(t[id] == 0) return;
    ll f = t[id];

    int left = id<<1;

    t[left] += f;
    t[left|1] += f;
    st[left] += f;
    st[left|1] += f;

    t[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id] += val;
        t[id] += val;
        return;
    }

    down(id);
    int mid = l + ((r-l)>>1);
    int left = id<<1;

    update(left,l,mid,u,v,val);
    update(left|1,mid+1,r,u,v,val);

    st[id] = max(st[left], st[left|1]);
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return -1e18;
    if(l >= u && r <= v){
        return st[id];
    }

    down(id);
    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return max(get(left,l,mid,u,v), get(left|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1,1,n);

    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int l,r,val;
            cin >> l >> r >> val;
            update(1,1,n,l,r,val);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << '\n';
        }
    }

    return NAH_I_WOULD_WIN;
}