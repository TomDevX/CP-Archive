/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-30 08:22:36
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Educational Segment Tree Contest - ITEZ2
 *    source: https://oj.vnoi.info/problem/segtree_itez2
 *    submission: https://oj.vnoi.info/submission/11984622
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree
 *    complexity: O(n \log n)
 *    note: Typical Segment tree sum query
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
    if(!fopen("segtree_itez2.INP", "r")) return;
    freopen("segtree_itez2.INP", "r", stdin);
    freopen("segtree_itez2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
ll st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, int val){
    if(l == r){
        st[id] = val;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(pos <= mid){
        update(lc,l,mid,pos,val);
    }
    else update(lc|1,mid+1,r,pos,val);

    st[id] = st[lc] + st[lc|1];
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return get(lc,l,mid,u,v) + get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    while(q--){
        int type;
        cin >> type;
        if(type == 2){
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << '\n';
        }
        else{
            int pos,x;
            cin >> pos >> x;
            update(1,1,n,pos,x);
        }
    }
    
    return NAH_I_WOULD_WIN;
}