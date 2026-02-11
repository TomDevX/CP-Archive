/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-11 14:45:10
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Rectangle Cutting
 *    source: https://cses.fi/problemset/task/1744
 *    submission: 
 *    status: WA
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,m;
    cin >> n >> m;
    vii dp(n+1,vi(m+1));
    for(int i = 2; i <= n; i++){
        dp[i][1] = i-1;
    }
    for(int j = 2; j <= m; j++){
        dp[1][j] = j-1;
    }

    for(int i = 2; i <= n; i++){
        for(int j = 2; j <= m; j++){
            if(i == j) continue;
            
            if(i > j){
                dp[i][j] = dp[i-j][j] + 1;
            }
            else dp[i][j] = dp[i][j-i] + 1;
        }
    }

    cout << dp[n][m];
}