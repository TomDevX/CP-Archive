/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-08 20:58:33
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Cắt hình chữ nhật
 *    source: https://marisaoj.com/problem/150
 *    submission: https://marisaoj.com/submission/1156452
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP
 *    complexity: O(n^3)
 *    note: Let dp[i][j] = min cut to make cells from (1,1) -> (i,j) into squares. In each iteration of i and j, we loop through k 2 times, which is the index of our cut by horizon or vertical way, each time we divide, we have 2 sectors that is k and i-k, use that in dp formula.
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
    if(!fopen("150.INP", "r")) return;
    freopen("150.INP", "r", stdin);
    freopen("150.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,m;
    cin >> n >> m;

    vvi dp(n+1, vi(m+1));
    dp[1][1] = 0;

    for(int i = 2; i <= n; i++) dp[i][1] = dp[i-1][1] + 1;
    for(int j = 2; j <= m; j++) dp[1][j] = dp[1][j-1] + 1;

    for(int i = 2; i <= n; i++){
        for(int j = 2; j <= m; j++){
            if(i == j) continue;
            dp[i][j] = 1e9;
            int &cur = dp[i][j];
            for(int k = 1; k < i; k++){
                cur = min(cur, dp[k][j] + dp[i-k][j]);
            }
            for(int k = 1; k < j; k++){
                cur = min(cur, dp[i][k] + dp[i][j-k]);
            }
            cur++;
        }
    }

    cout << dp[n][m];
    
    return NAH_I_WOULD_WIN;
}