/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-09 21:13:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Fences painting    
 *    source: https://marisaoj.com/problem/574
 *    submission: https://marisaoj.com/submission/1117055
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: We have 2 ways to add colors at index i, one is yellow (y), and one is orange (o), if we add yellow, there won't be any change to the previous dp results so we add the whole previous results. If we add orange color at i, we can only take another orange at index i-k => [i-k+1,i-1] must be yellow
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("debuggingz.h")
#include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#ifdef LOCAL
    #include <iomanip>
    #include <ctime>
    #define NAH_I_WOULD_WIN cerr << "\033[32m\n[Runtime: " << fixed << setprecision(3) << 1.0*clock()/CLOCKS_PER_SEC << "s]\033[0m\n", 0
#else
    #define NAH_I_WOULD_WIN 0
#endif

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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

void setup(){
    if(!fopen("574.INP", "r")) return;
    freopen("574.INP", "r", stdin);
    freopen("574.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;
    vll dp(n+1);
    dp[0] = 1;

    for(int i = 1; i <= n; i++){
        dp[i] = (dp[max(i-k,0)] + dp[i-1])%MOD;
    }

    cout << dp[n];
    
    return NAH_I_WOULD_WIN;
}