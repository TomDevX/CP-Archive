/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-09 21:46:07
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Knapsack 2 
 *    source: https://marisaoj.com/problem/141
 *    submission: https://marisaoj.com/submission/1117110
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n \cdot S)
 *    note: Typical Knapsack DP
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
    if(!fopen("141.INP", "r")) return;
    freopen("141.INP", "r", stdin);
    freopen("141.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct box{
    int w,v;
    
    box(int _w = 0, int _v = 0) : w(_w), v(_v) {};
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,S;
    cin >> n >> S;

    vector<box> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].w >> a[i].v;
    }

    vll dp(S+1);

    for(int i = 1; i <= n; i++){
        for(int j = S; j >= a[i].w; j--){
            dp[j] = max(dp[j], dp[j-a[i].w] + a[i].v);
        }
    }

    cout << dp[S];
    
    return NAH_I_WOULD_WIN;
}