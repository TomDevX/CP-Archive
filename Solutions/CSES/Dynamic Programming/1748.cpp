/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-13 07:40:47
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Increasing Subsequence II
 *    source: https://cses.fi/problemset/task/1748
 *    submission: https://cses.fi/problemset/result/16251418/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Range Query
 *    complexity: O(n \log n)
 *    note: We use coordinate compression to compress the value of the elements to below 2e5. Let dp[i] = the number of LIS from 1 -> n, the formula of DP is dp[i] = sum(dp[1 -> i-1]) + 1. Because we can connect the current element with any previous smaller value and we have a LIS with only the current element.
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
const ll MOD = 1e9+7;
int st[4*N];

// ----------------------- [ FUNCTIONS ] -----------------------
int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return (get(left,l,mid,u,v) + get(left|1,mid+1,r,u,v))%MOD;
}

void update(int id, int l, int r, int pos, int val){
    if(l == r){
        st[id] = (st[id]+val)%MOD;
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    if(pos <= mid) update(left,l,mid,pos,val);
    else update(left|1,mid+1,r,pos,val);
    st[id] = (st[left] + st[left|1])%MOD;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    vi a(n+1);

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    // coordinate compression
    vi sorted = a;
    sort(all(sorted,1));
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(all(sorted,1),a[i]) - sorted.begin();
    }

    dbg(a,1);

    // use segment tree to get the lower values' DP result
    int ans = 0;
    for(int i = 1; i <= n; i++){
        int cur = get(1,1,n,1,a[i]-1) + 1;
        ans = (ans + cur)%MOD;
        update(1,1,n,a[i],cur);
    }

    cout << ans;
}