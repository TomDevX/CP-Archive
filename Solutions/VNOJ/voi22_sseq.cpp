/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-10 08:19:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: VOI 22 Bài 4 - Đoạn số
 *    source: https://oj.vnoi.info/problem/voi22_sseq
 *    submission: https://oj.vnoi.info/submission/12080379
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree Lazy, VOI
 *    complexity: O(n \log n)
 *    note: My initial idea was using prefix sum in [l;r] range for each segments, and then use segment tree to find best pref[r] - pref[l-1], but the problem here is prefix sum can't manage if any [l;r] is overlapping. So now we use segment tree lazy, we sort the segments by r increasing, we iterate through all segments and try to fix b as the current segment's r. Now we add w to [0;a[i].l] and query for the max value in the whole array to choose for the best a for our current b
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
    if(!fopen("SSEQ.INP", "r")) return;
    freopen("SSEQ.INP", "r", stdin);
    freopen("SSEQ.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int L = 1e6;

struct node{
    int l,r,w;

    node(int _l = 0, int _r = 0, int _w = 0) : l(_l), r(_r), w(_w) {};
    bool operator<(const node& other) const{
        return r < other.r;
    }
};

ll st[4*L + 2], t[4*L + 2];

// ----------------------- [ FUNCTIONS ] -----------------------
void down(int id){
    if(t[id] == 0) return;
    ll f = t[id];
    t[id] = 0;

    int lc = id<<1;

    t[lc] += f;
    t[lc|1] += f;
    st[lc] += f;
    st[lc|1] += f;
}

void update(int id, int l, int r, int u, int v, int val){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        t[id] += val;
        st[id] += val;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;
    down(id);

    update(lc,l,mid,u,v,val);
    update(lc|1,mid+1,r,u,v,val);

    st[id] = max(st[lc], st[lc|1]);
}
// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vector<node> a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].w;

    sort(all(a,1));

    ll ans = 0;
    for(int i = 1; i <= n; i++){
        update(1,0,L,0,a[i].l,a[i].w);
        ans = max(ans, st[1]);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}