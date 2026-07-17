/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-14 07:33:12
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: XORQ
 *    source: https://oj.vnoi.info/problem/fcb048_xorq
 *    submission: https://oj.vnoi.info/submission/12115017
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree Lazy
 *    complexity: O(n \cdot \log n \cdot  \log a[i] \cdot n)
 *    note: Count the bit 1 of every position and save it for the segment, when getting the result we get the number of turned on bits
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
    if(!fopen("fcb048_xorq.INP", "r")) return;
    freopen("fcb048_xorq.INP", "r", stdin);
    freopen("fcb048_xorq.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int a[N];

int st[4*N][21], t[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        for(int i = 20; i >= 0; i--){
            if(a[l] >> i & 1) st[id][i]++;
        }
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    for(int i = 20; i >= 0; i--){
        st[id][i] = st[lc][i] + st[lc|1][i];
    }
}

void down(int id, int l, int r){
    if(t[id] == 0) return;
    int f = t[id];
    t[id] = 0;

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    t[lc] ^= f;
    t[lc|1] ^= f;

    for(int i = 20; i >= 0; i--){
        if(f >> i & 1){
            st[lc][i] = (mid-l+1) - st[lc][i];
            st[lc|1][i] = (r-mid) - st[lc|1][i];
        }
    }
}

void update(int id, int l, int r, int u, int v, int val){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        t[id] ^= val;
        for(int i = 20; i >= 0; i--){
            if(val >> i & 1){
                st[id][i] = (r-l+1) - st[id][i];
            }
        }
        return;
    }

    down(id, l, r);
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    update(lc,l,mid,u,v,val);
    update(lc|1,mid+1,r,u,v,val);

    for(int i = 20; i >= 0; i--){
        st[id][i] = st[lc][i] + st[lc|1][i];
    }
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v){
        ll sum = 0;
        for(int i = 20; i >= 0; i--){
            sum += (1LL << i)*st[id][i];
        }
        return sum;
    }

    down(id,l,r);
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return get(lc,l,mid,u,v) + get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    build(1,1,n);

    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << '\n';
        }
        else{
            int l,r,x;
            cin >> l >> r >> x;
            update(1,1,n,l,r,x);
        }
    }
    
    return NAH_I_WOULD_WIN;
}