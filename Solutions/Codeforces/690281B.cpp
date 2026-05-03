/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-03 22:15:36
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Tăng dãy
 *    source: https://codeforces.com/gym/690281/problem/B
 *    submission: https://codeforces.com/gym/690281/submission/373439975
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree Beats
 *    complexity: O((n \cdot k + q) \log n)
 *    note: We use typical segment tree beats I think, with 4 main variable is that: sum, lazy, dis (min gap from a value to its nearest S), active (counts ai that didn't = its S). Now if our dis is reached, we just do the recursion down and then update for the child, then push up to parent nodes. Notice that when binary search for value in S, you need to use int pos instead of iterator it because it make our program very slow (lead to TLE).
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
const int INF = 2e9;
int a[N], S[10];
int n,q,k;

struct node{
    ll sum = 0, lazy = 0;
    int dis = 0, active = 0;

    node(ll _sum = 0, ll _lazy = 0, int _dis = INF, int _active = 0) : 
    sum(_sum), lazy(_lazy), dis(_dis), active(_active) {};
};

node st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
node merge(const node A, const node B){
    return node(
        A.sum + B.sum,
        0,
        min(A.dis,B.dis),
        A.active + B.active
    );
}

void build(int id, int l, int r){
    if(l == r){
        st[id].sum = a[l];
        int pos = lower_bound(S + 1, S + k + 1, st[id].sum) - S;
        if(pos > k){
            st[id] = node(st[id].sum, 0, INF, 1);
        }
        else if(S[pos] == st[id].sum){
            st[id] = node(st[id].sum, 0, INF, 0);
        }
        else{
            st[id] = node(st[id].sum, 0, S[pos] - st[id].sum, 1);
        }
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    build(lc,l,mid);
    build(lc|1,mid+1,r);

    st[id] = merge(st[lc], st[lc|1]);
}

inline void apply(int id, ll val){
    if(st[id].active == 0) return;
    st[id].sum += val*st[id].active;
    st[id].lazy += val;
    if(st[id].dis != INF) st[id].dis -= val;
}

inline void down(int id){
    if(st[id].lazy == 0) return;
    apply(id << 1, st[id].lazy);
    apply(id << 1 | 1, st[id].lazy);
    st[id].lazy = 0;
}


void update(int id, int l, int r, int u, int v, ll val){
    if(l > v || r < u || (id < 4*N && st[id].active == 0)) return;

    if(l >= u && r <= v && val < st[id].dis){
        apply(id,val);
        return;
    }

    if(l == r){ 
        st[id].sum += val;

        int pos = lower_bound(S + 1, S + k + 1, st[id].sum) - S;
        if(pos > k){
            st[id] = node(st[id].sum, 0, INF, 1);
        }
        else if(S[pos] == st[id].sum){
            st[id] = node(st[id].sum, 0, INF, 0);
        }
        else{
            st[id] = node(st[id].sum, 0, S[pos] - st[id].sum, 1);
        }
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    down(id);
    update(lc,l,mid,u,v,val);
    update(lc|1,mid+1,r,u,v,val);

    st[id] = merge(st[lc], st[lc|1]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= k; i++) cin >> S[i];
    sort(S + 1, S + k + 1);

    build(1,1,n);

    while(q--){
        int l,r,x;
        cin >> l >> r >> x;
        update(1,1,n,l,r,x);
        cout << st[1].sum << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}