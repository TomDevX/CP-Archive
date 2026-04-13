/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-11 00:28:17
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bài toán bông hoa
 *    source: https://oj.vnoi.info/problem/atcoder_dp_q
 *    submission: https://oj.vnoi.info/submission/12088968
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP, Segment Tree
 *    complexity: O(n \log n)
 *    note: At first, we dp this problem. dp[i] = a[i] + max(dp[1 -> j] which h[j] < h[i]), this takes us O(n^2) => Use segment tree on h[i] values to optimize
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
    if(!fopen("atcoder_dp_q.INP", "r")) return;
    freopen("atcoder_dp_q.INP", "r", stdin);
    freopen("atcoder_dp_q.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

ll st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, ll val){
    if(l == r){
        st[id] = max(st[id],val);
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(pos <= mid) update(lc,l,mid,pos,val);
    else update(lc|1,mid+1,r,pos,val);

    st[id] = max(st[lc],st[lc|1]);
}

ll get_max(int id, int l, int r ,int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return max(get_max(lc,l,mid,u,v), get_max(lc|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vi h(n+1), a(n+1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    for(int i = 1; i <= n; i++) cin >> a[i];

    ll ans = 0;
    for(int i = 1; i <= n; i++){
        ll x = a[i] + get_max(1,1,n,1,h[i]-1);
        update(1,1,n,h[i],x);
        ans = max(ans,x);
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}