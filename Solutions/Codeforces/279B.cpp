/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-16 22:49:15
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Books
 *    source: https://codeforces.com/problemset/problem/279/B
 *    submission: https://codeforces.com/problemset/submission/279/366993295
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Searching, Greedy
 *    complexity: O(n \log n)
 *    note: According to the problem statement, we can only select a subarray of books to read, so that we know its sum must not higher than t. So that we need to make a prefix sum, and then binary search at each index i to get the farthest index to the right, and that is also the longest lenth you can read when you start at i
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <algorithm>

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
    if(!fopen("279B.INP", "r")) return;
    freopen("279B.INP", "r", stdin);
    freopen("279B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,t;
    cin >> n >> t;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vi pref(n+1);
    for(int i = 1; i <= n; i++) pref[i] = pref[i-1] + a[i];

    int ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, (int)(upper_bound(pref.begin() + i, pref.end(), t+pref[i-1]) - pref.begin()) - i + 1 - 1);
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}