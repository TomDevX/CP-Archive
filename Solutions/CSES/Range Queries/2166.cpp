/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-03 00:42:08
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Prefix Sum Queries
 *    source: https://cses.fi/problemset/task/2166
 *    submission: https://cses.fi/problemset/result/17063144/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree
 *    complexity: O(n \log n)
 *    note: I thought it was more complex at first (I misread the statement and thought I need to print the subarray with max value, but turns out I just need max pref). Let's divide our segment into 2 halves and assume they already have their answers to its best prefix sum, to get the max of current pref, there are only 2 cases: 1 is best prefix sum of first half, 2 is sum of first half + best prefix sum of second half. Now we just need to get max of those 2 cases. Remember the case 0, if value < 0, we need to let pref = 0
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
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
    if(!fopen("2166.INP", "r")) return;
    freopen("2166.INP", "r", stdin);
    freopen("2166.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

struct node{
    ll sum, pref;

    node(ll _sum = 0, ll _pref = 0) : 
    sum(_sum), pref(_pref) {};
};

node st[4*N];
int n,q;
int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
node merge(const node x, const node y){
    return node(
        x.sum + y.sum, // sum
        max({0LL,x.pref, x.sum + y.pref}) // pref
    );
}

void build(int id, int l, int r){
    if(l == r){
        st[id].sum = a[l];
        if(a[l] > 0){
            st[id].pref = a[l];
        }
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = merge(st[lc], st[lc|1]);
}

void update(int id, int l, int r, int pos, int val){
    if(l == r){
        st[id].sum = val;
        if(val > 0){
            st[id].pref = val;
        }
        else st[id].pref = 0;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(pos <= mid) update(lc,l,mid,pos,val);
    else update(lc|1,mid+1,r,pos,val);

    st[id] = merge(st[lc], st[lc|1]);
}

node get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return merge(get(lc,l,mid,u,v), get(lc|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1,1,n);

    dbg(get(1,1,n,1,n).pref,1);
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int pos,x;
            cin >> pos >> x;
            update(1,1,n,pos,x);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r).pref << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}