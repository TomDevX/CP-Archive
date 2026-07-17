/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-10 20:39:08
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Range Updates and Sums
 *    source: https://cses.fi/problemset/task/1735
 *    submission: https://cses.fi/problemset/result/16866469/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree Lazy
 *    complexity: O(n \log n)
 *    note: If we divide our 2 queries into 2 different arrays, we can't manage which come first, which come after. So we now prioritize the set command first, and then add command later, the set command will delete all previous in-queue lazy add commands
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <bitset>

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
    if(!fopen("1735.INP", "r")) return;
    freopen("1735.INP", "r", stdin);
    freopen("1735.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n;
int cnt = 0;
const int N = 2e5+2;

int a[N];
const int M = 4*N;
ll st[M], t[M];
bitset<M> hasSet;

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

void down(int id, int l, int r){
    if(t[id] == 0) return;
    ll f = t[id];
    t[id] = 0;
    
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(hasSet[id]){
        t[lc] = t[lc|1] = f;
    }
    else{
        t[lc] += f;
        t[lc|1] += f;
    }

    if(hasSet[id]){
        st[lc] = 1LL*(mid-l+1)*f;
        st[lc|1] = 1LL*(r-mid)*f;
        hasSet[id] = 0;
        hasSet[lc] = hasSet[lc|1] = 1;
    }
    else{
        st[lc] += 1LL*(mid-l+1)*f;
        st[lc|1] += 1LL*(r-mid)*f;
    }

}

void update_add(int id, int l, int r, int u, int v, int x){
    if(l > v || r < u ) return;
    if(l >= u && r <= v){
        t[id] += x;
        if(!hasSet[id]) st[id] += 1LL*(r-l+1)*x;
        else st[id] = 1LL*(r-l+1)*t[id];
        return;
    }

    down(id,l,r);
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    update_add(lc,l,mid,u,v,x);
    update_add(lc|1,mid+1,r,u,v,x);

    st[id] = st[lc] + st[lc|1];
}

void update_set(int id, int l, int r, int u, int v, int x){
    if(l > v || r < u ) return;
    if(l >= u && r <= v){
        t[id] = x;
        hasSet[id] = 1;
        st[id] = 1LL*(r-l+1)*x;
        return;
    }
    
    down(id,l,r);
    int mid = l + ((r-l)>>1);
    int lc = id<<1;
    
    update_set(lc,l,mid,u,v,x);
    update_set(lc|1,mid+1,r,u,v,x);
    st[id] = st[lc] + st[lc|1];
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    down(id,l,r);
    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return get(lc,l,mid,u,v) + get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    int q;
    cin >> q;

    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1,1,n);

    while(q--){
        int type;
        cin >> type;
        cnt++;
        if(type == 1){
            int l,r,x;
            cin >> l >> r >> x;
            update_add(1,1,n,l,r,x);
        }
        else if(type == 2){
            int l,r,x;
            cin >> l >> r >> x;
            update_set(1,1,n,l,r,x);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}