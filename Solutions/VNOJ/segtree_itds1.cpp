/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-30 08:38:57
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Educational Segment Tree Contest - ITDS1
 *    source: https://oj.vnoi.info/problem/segtree_itds1
 *    submission: https://oj.vnoi.info/submission/11984756
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree, Lower Bound
 *    complexity: O(n \log n)
 *    note: To search for the element that is >= k, we use multiset, so our segment tree will store multisets
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <set>

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
    if(!fopen("segtree_itds1.INP", "r")) return;
    freopen("segtree_itds1.INP", "r", stdin);
    freopen("segtree_itds1.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
multiset<int> st[4*N];
int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id].insert(a[l]);
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = st[lc];
    st[id].insert(st[lc|1].begin(),st[lc|1].end());
}

void update(int id, int l, int r, int pos, int val, int old){
    if(l == r){
        st[id] = {val};
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(pos <= mid){
        update(lc,l,mid,pos,val,old);
    }
    else update(lc|1,mid+1,r,pos,val,old);

    st[id].erase(st[id].find(old));
    st[id].insert(val);
}

int get(int id, int l, int r, int u, int v, int k){
    if(l > v || r < u) return 2e9;
    if(l >= u && r <= v){
        multiset<int>::iterator it = st[id].lower_bound(k);
        return (it == st[id].end() ? 2e9 : *it);
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return min(get(lc,l,mid,u,v,k), get(lc|1,mid+1,r,u,v,k));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1,1,n);

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int pos,val;
            cin >> pos >> val;
            update(1,1,n,pos,val, a[pos]);
            a[pos] = val;
        }
        else{
            int l,r,k;
            cin >> l >> r >> k;
            int ans =  get(1,1,n,l,r,k);
            cout << (ans != 2e9 ? ans : -1) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}