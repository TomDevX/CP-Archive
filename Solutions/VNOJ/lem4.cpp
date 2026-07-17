/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-10 09:12:48
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: WHITE BLACK
 *    source: https://oj.vnoi.info/problem/lem4
 *    submission: https://oj.vnoi.info/submission/12081676
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree
 *    complexity: O(n \log n)
 *    note: To have the answer for the current continuous subarray, we make a node with prefix, suffix and current best answer to be able to combine with other nodes in the future. If the range is updated to 1, the whole inside segment will have the best ans of r-l+1. But now we update range so we use lazy segment tree.
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
    if(!fopen("lem4.INP", "r")) return;
    freopen("lem4.INP", "r", stdin);
    freopen("lem4.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
const int N = 1e4;

struct node{
    int ans, pref, suff;

    node(int _ans = 0, int _pref = 0, int _suff = 0) : ans(_ans), pref(_pref), suff(_suff) {};
};


node st[4*N+2];
int t[4*N+2];

// ----------------------- [ FUNCTIONS ] -----------------------
node merge(const node& x, const node& y, int l, int r, int u, int v){
    int pref = (x.pref == r - l + 1 ? x.pref + y.pref : x.pref);
    int suff = (y.suff == v - u + 1 ? x.suff + y.suff : y.suff);
    return node(
        max({x.ans,y.ans,x.suff + y.pref, x.pref, y.suff}),
        pref,
        suff
    );
}

void build(int id, int l, int r){
    if(l == r){
        st[id] = node(r-l+1,r-l+1,r-l+1);
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = merge(st[lc], st[lc|1], l, mid, mid + 1 ,r);
}

void down(int id, int l, int r){
    if(t[id] == 0) return;
    int lc = id<<1;
    int mid = l + ((r-l)>>1);

    t[lc] = t[id];
    t[lc|1] = t[id];
    int addl = (t[id] == 1 ? mid-l+1 : 0);
    st[lc] = node(addl, addl, addl);
    int addr = (t[id] == 1 ? r-mid : 0);
    st[lc|1] = node(addr,addr, addr);

    t[id] = 0;
}

void update(int id, int l, int r, int u, int v, int type){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        if(type == 1) st[id].ans = st[id].pref = st[id].suff = r-l+1;
        else st[id].ans = st[id].pref = st[id].suff = 0;
        t[id] = type;
        return;
    }

    down(id,l,r);
    int mid = l  + ((r-l)>>1);
    int lc = id<<1;


    update(lc,l,mid,u,v,type);
    update(lc|1,mid+1,r,u,v,type);

    st[id] = merge(st[lc], st[lc|1], l, mid, mid+1,r);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    int q;
    cin >> q;

    build(1,1,n);

    // 0: white | 1: black
    while(q--){
        int type;
        cin >> type;
        if(type == 1 || type == 2){
            int l,r;
            cin >> l >> r;
            update(1,1,n,l,r,type);
        }
        else{
            cout << st[1].ans << '\n';
        }
    }

    cerr << st[1].ans << ' ' << st[1].pref << ' ' << st[1].suff << ' ' << t[1];
    
    return NAH_I_WOULD_WIN;
}