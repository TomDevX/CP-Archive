/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-20 15:55:34
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Little Girl and Maximum Sum
 *    source: https://codeforces.com/problemset/problem/276/C
 *    submission: https://codeforces.com/contest/276/submission/367460597
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n \log n)
 *    note: To get the max sum, we should put the largest value into the most used position, and so on to pair the i^{th} largest value with i^{th} most used position. To count the used time of position, we use prefix sum of diff array
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
    if(!fopen("276C.INP", "r")) return;
    freopen("276C.INP", "r", stdin);
    freopen("276C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(all(a,1));

    vi cnt(n+2);

    while(q--){
        int l,r;
        cin >> l >> r;
        cnt[l]++;
        cnt[r+1]--;
    }

    for(int i = 2; i <= n; i++){
        cnt[i] += cnt[i-1];
    }

    sort(range(cnt,1,n));

    ll ans = 0;
    for(int i = 1; i <= n; i++){
        ans += 1LL*a[i]*cnt[i];
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}