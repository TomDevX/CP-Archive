/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-10 16:09:56
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Hall   
 *    source: https://marisaoj.com/problem/575
 *    submission: https://marisaoj.com/submission/1117926
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: I use DP on the time, let dp[i] = best total usage time from time 1 -> i
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
    if(!fopen("575.INP", "r")) return;
    freopen("575.INP", "r", stdin);
    freopen("575.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5;
struct box{
    int st,ed;

    box(int _st = 0, int _ed = 0) : st(_st), ed(_ed){};
    bool operator<(const box& other) const{
        return ed < other.ed;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;

    vector<box> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].st >> a[i].ed;
    }   

    sort(all(a,1));

    vi dp(N+2);
    
    int best = 0;

    for(int i = 1; i <= n; i++){
        for(int j = a[i-1].ed + 1; j < a[i].ed; j++) dp[j] = best; // cover all empty spaces with the best previous option

        dp[a[i].ed] = max(best,dp[a[i].st-1] + a[i].ed - a[i].st + 1); // update if choosing this option in better than keeping the old one
        best = max(best, dp[a[i].ed]);
    }

    cout << *max_element(all(dp,1));
    
    return NAH_I_WOULD_WIN;
}