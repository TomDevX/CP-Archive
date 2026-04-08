/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-08 21:25:55
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Truy vấn palindrome
 *    source: https://marisaoj.com/problem/153
 *    submission: https://marisaoj.com/submission/1156483
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP
 *    complexity: O(n^2) 
 *    note: Let dp[l][r] = is s(l -> r) a palindrome. We check if the previous status (dp[l+1][r-1]) and the current character (a[l] & a[r]) is equal
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
    if(!fopen("153.INP", "r")) return;
    freopen("153.INP", "r", stdin);
    freopen("153.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;
    int n = sz(s);
    s = "#" + s;

    vector<vector<bool>> dp(n+1,vector<bool>(n+1));
    for(int i = 1; i <= n; i++) dp[i][i] = 1;
    for(int i = 1; i < n; i++) if(s[i] == s[i+1]) dp[i][i+1] = 1;

    for(int len = 3; len <= n; len++){
        for(int i = 1; i + len - 1 <= n; i++){
            int j = i + len - 1;
            dp[i][j] = (dp[i+1][j-1] && s[i] == s[j] ? 1 : 0);
        }
    }

    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << (dp[l][r] ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}