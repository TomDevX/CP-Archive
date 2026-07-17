/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-11 00:46:10
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Polynomial Queries
 *    source: https://cses.fi/problemset/task/1736
 *    submission: https://cses.fi/problemset/result/16867163/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree Lazy Polynominal
 *    complexity: O(n \log n)
 *    note: we have each a[i] added in range [l;r] by (i-l+1). So we need to add sum(i: l -> r | i - l + 1) = sum(i: l -> r | i) + (r-l+1)*(1-l). We divide the part sum(i: l -> r | i) and (r-l+1)*(1-l) into 2 lazy arrays, and then process them. Note that sum(l -> r) = (r-l+1)*(l+r)/2
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
    if(!fopen("1736.INP", "r")) return;
    freopen("1736.INP", "r", stdin);
    freopen("1736.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int n;
int a[N];

ll st[4*N], ti[4*N], t_const[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void build(int id, int l, int r){
    if(l == r){
        st[id] = a[l];
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = st[lc] + st[lc|1];
}

ll sum(int l, int r){
    return 1LL*(r-l+1)*(l+r)/2LL;
}

void down(int id, int l, int r){
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(ti[id]){
        int f = ti[id];
        ti[id] = 0;

        ti[lc] += f;
        ti[lc|1] += f;

        st[lc] += 1LL*f*sum(l,mid);
        st[lc|1] += 1LL*f*sum(mid+1,r);
    }

    if(t_const[id]){
        ll f = t_const[id];
        t_const[id] = 0;

        t_const[lc] += f;
        t_const[lc|1] += f;

        st[lc] += f*(mid-l+1);
        st[lc|1] += f*(r-mid);
    }
}

void update(int id, int l, int r, int u, int v){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id] += 1LL*sum(l,r) + 1LL*(r-l+1)*(1-u);
        ti[id]++;
        t_const[id] += 1-u;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;
    down(id,l,r);

    update(lc,l,mid,u,v);
    update(lc|1,mid+1,r,u,v);

    st[id] = st[lc] + st[lc|1];
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v ) return st[id];

    down(id,l,r);
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return get(lc,l,mid,u,v) + get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1,1,n);

    while(q--){
        int type,l,r;
        cin >> type >> l >> r;
        if(type == 1){
            update(1,1,n,l,r);
        }
        else{
            cout << get(1,1,n,l,r) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}