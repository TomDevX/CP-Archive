/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-04 00:13:33
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Canh gác bảo tàng
 *    source: https://lqdoj.edu.vn/problem/canhgacbt
 *    submission: https://lqdoj.edu.vn/submission/8343061
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Segment Tree, Dynamic Programming
 *    complexity: O(n \log n)
 *    note: Beware that the problem statement is kinda misunderstand because if the ith guard fill in [st;ed] so ed is not occupied yet, and ed maybe > n. Let dp[i] = min cost to fill all the gap in [0;a[i].ed] and we must choose guard i, in order to not let any gap, we have to let dp[i] = min(dp[st -> ed-1]) + a[i].c. For brute force, we can iterate another pointer to get the min value of dp in that range. But what solves a range problem better than segment tree? So we use segment tree to optimize this.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>

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
    if(!fopen("GALLERY.INP", "r")) return;
    freopen("GALLERY.INP", "r", stdin);
    freopen("GALLERY.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct Guard{
    int st,ed,c;

    Guard(int _st = 0, int _ed = 0, int _c = 0) : st(_st), ed(_ed), c(_c) {};
    bool operator<(const Guard& other) const{
        return ed < other.ed;
    }
};
const int N = 1e5;
ll st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, ll val){
    if(l == r){
        st[id] = min(st[id], val);
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(pos <= mid) update(lc,l,mid,pos,val);
    else update(lc|1,mid+1,r,pos,val);

    st[id] = min(st[lc], st[lc | 1]);
}

ll get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 2e18;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return min(get(lc,l,mid,u,v), get(lc|1,mid+1,r,u,v));
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(st,0x3f,sizeof(st));
    
    int n,m;
    cin >> n >> m;

    vector<Guard> a(m+1);
    for(int i = 1; i <= m; i++){
        cin >> a[i].st >> a[i].ed >> a[i].c;
    }
    sort(all(a,1));

    vll dp(m+1,2e18);
    for(int i = 1; i <= m; i++){
        if(a[i].st == 0){
            dp[i] = a[i].c;
            update(1,0,n,a[i].ed,a[i].c);
        }
    }

    for(int i = 1; i <= m; i++){
        ll val = get(1,0,n,a[i].st,a[i].ed-1);
        dp[i] = val + a[i].c;
        update(1,0,n,a[i].ed,dp[i]);
    }


    ll ans = 2e18;
    for(int i = 1; i <= m; i++){
        if(a[i].ed >= n) ans = min(ans, dp[i]);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}