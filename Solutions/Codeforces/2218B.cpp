/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-20 16:15:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: The 67th 6-7 Integer Problem
 *    source: https://codeforces.com/problemset/problem/2218/B
 *    submission: https://codeforces.com/contest/2218/submission/370657307
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log n)
 *    note: Just make the smallest numbers negative so we get the max sum
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
    if(!fopen("go.INP", "r")) return;
    freopen("go.INP", "r", stdin);
    freopen("go.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    int n = 7;
    while(tc--){
        vi a(n+1);
        for(int i = 1; i <= n; i++) cin>>a[i];
        sort(all(a,1));
        ll sum = 0;
        for(int i = 1; i <= 6; i++) sum -= a[i];
        cout << sum + a[n] << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}