/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-18 23:40:12
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: USACO 2021 US Open, Gold - Problem 1. United Cows of Farmer John
 *    source: https://usaco.org/index.php?page=viewproblem2&cpid=1137
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BIT
 *    complexity: O(n \log n)
 *    note: To get the right range, we need to ensure 2 conditions, let assume that we are processing value index r. suff[r] is nearest position to the right which has the same value as a[r], pref[r] is the same as suff[r] but on left side. Assume that at r, we choose l, we need to satisfy: l > pref[r] && r < suff[l]. To get that, we need to pre-processing r indices first, add them to event array, and update them like a diff array. And then just iterate through l and update diff array if satisfied.
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
    if(!fopen("1137.INP", "r")) return;
    freopen("1137.INP", "r", stdin);
    freopen("1137.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int n;

vpii events[N];
int a[N], suff[N], pref[N], pos[N], bit[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int x, int val){
    for(; x <= n; x += x&-x){
        bit[x] += val;
    }
}

int get(int x){
    int res = 0;
    for(; x; x -= x&-x){
        res += bit[x];
    }
    return res;
}

int query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++){
        if(pos[a[i]]) pref[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for(int i = 1; i <= n; i++) pos[a[i]] = n+1;
    for(int i = n; i >= 1; i--){
        suff[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for(int r = 1; r <= n; r++){
        events[pref[r]+1].eb(r,1);
        events[r].eb(r,-1);
    }

    ll ans = 0;
    for(int l = 1; l <= n; l++){
        for(const pii &p : events[l]) update(p.fi,p.se);

        ans += query(l+1,suff[l]-1);
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}