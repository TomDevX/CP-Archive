/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-20 16:15:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Reading
 *    source: https://codeforces.com/contest/234/problem/B
 *    submission: https://codeforces.com/contest/234/submission/370650351
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sortings
 *    complexity: O(n \log n)
 *    note: Just sort the array and get the k largest
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
    if(!fopen("input.txt", "r")) return;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;
    vpii a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i].fi, a[i].se = i;
    sort(rall(a,1));

    cout << a[k].fi << '\n';
    vi ans;
    for(int i = 1; i <= k; i++) ans.eb(a[i].se);
    sort(all(ans,0));
    for(int i : ans) cout << i << ' ';
    
    return NAH_I_WOULD_WIN;
}