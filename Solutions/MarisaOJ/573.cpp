/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-08 21:32:42
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Marisa
 *    source: https://marisaoj.com/problem/573
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

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
    if(!fopen("573.INP", "r")) return;
    freopen("573.INP", "r", stdin);
    freopen("573.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int MOD  = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;
    int n = sz(s);
    s = "#" + s;

    string t = "#marisa";
    int m = sz(t) - 1;

    vvi dp(n+1,vi(m+1));
    vvi cnt(n+1,vi(m+1));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s[i] == t[j]){
                dp[i][j] = (dp[i-1][j-1] + 1)%MOD;
                cnt[i][j] = cnt[i-1][j-1];
            }
            else{
                if(dp[i][j-1] > dp[i-1][j]){
                    cnt[i][j] = cnt[i][j-1];
                    dp[i][j] = dp[i][j-1];
                }
                else if(dp[i-1][j] > dp[i][j-1]){
                    cnt[i][j] = cnt[i-1][j];
                    dp[i][j] = dp[i-1][j];
                }
                else{
                    cnt[i][j] = (((cnt[i-1][j] + cnt[i][j-1])%MOD - cnt[i-1][j-1])%MOD + MOD)%MOD;
                }
            }
        }
    }
    cout << cnt[n][m];
    
    return NAH_I_WOULD_WIN;
}