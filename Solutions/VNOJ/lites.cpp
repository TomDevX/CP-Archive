/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-28 21:12:59
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bật đèn
 *    source: https://oj.vnoi.info/problem/lites
 *    submission: https://oj.vnoi.info/submission/11975680
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree
 *    complexity: O(n \log n)
 *    note: We know that the bulb will only have 2 states that are on and off, so if the number of toggle times is even, it will be an off, otherwise, it will be an on
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
    if(!fopen("lites.INP", "r")) return;
    freopen("lites.INP", "r", stdin);
    freopen("lites.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 1e5+2;
int st[4*N], t[4*N], a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void down(int id, int l, int r, int mid){
    if(t[id] == 0) return;
    t[id] = 0;

    int lc = id<<1;

    t[lc] = !t[lc];
    t[lc|1] = !t[lc|1];
    st[lc] = (mid-l+1) - st[lc];
    st[lc|1] = (r-mid) - st[lc|1];
}

void update(int id, int l, int r, int u, int v){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        st[id] = ((r-l+1) - st[id]);
        t[id] = !t[id];
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;
    down(id, l, r, mid);

    update(lc,l,mid,u,v);
    update(lc|1,mid+1,r,u,v);

    st[id] = st[lc] + st[lc|1];
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v){
        return st[id];
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;
    down(id, l, r, mid);

    return get(lc,l,mid,u,v) + get(lc|1,mid+1,r,u,v);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;

    while(q--){
        int type;
        cin >> type;
        if(type == 0){
            int l,r;
            cin >> l >> r;

            update(1,1,n,l,r);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}