/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-06 20:24:06
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Jealousy
 *    source: https://marisaoj.com/problem/160
 *    submission: https://marisaoj.com/submission/1113310
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: We can get streak from previous dps to avoid the 3 consecutive
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
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
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
ll dp[N][2][3];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    vi a(n+1),b(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    for(int i = 1; i <= n; i++){
        for(int person = 0; person < 2; person++){
            dp[i][person][1] = max({dp[i-1][!person][1], dp[i-1][!person][2]}) + (person ? b[i] : a[i]);
            dp[i][person][2] = max({dp[i-1][!person][1], dp[i-1][!person][2], dp[i-1][person][1]}) + (person ? b[i] : a[i]);
        }
    }

    ll ans = 0;
    for(int person = 0; person < 2; person++){
        for(int j = 1; j <= 2; j++){
            ans = max(ans, dp[n][person][j]);
        }
    }
    cout << ans;
}