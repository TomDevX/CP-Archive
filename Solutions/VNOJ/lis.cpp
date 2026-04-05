/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-21 22:24:10
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Dãy con tăng dài nhất (bản khó)
 *    source: https://oj.vnoi.info/problem/lis
 *    submission: https://oj.vnoi.info/submission/11927394
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n \log n)
 *    note: Typical LIS problem
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
    if(!fopen("lis.INP", "r")) return;
    freopen("lis.INP", "r", stdin);
    freopen("lis.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; ++i) cin >> a[i];

    vi lis;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        int it = lower_bound(all(lis,0), a[i]) - lis.begin();
        if(it == sz(lis)){
            lis.eb(a[i]);
            ans = sz(lis);
        }
        else lis[it] = a[i];
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}