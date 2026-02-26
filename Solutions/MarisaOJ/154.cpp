/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-26 10:37:47
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Unique subsequences
 *    source: https://marisaoj.com/problem/154
 *    submission: https://marisaoj.com/submission/1099777
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: Let dp[i] = number of valid subsequences which can be from 1 to n. dp[i] can get result from dp[i-1] because at dp[i-1] subsequences, we can choose to add the i_th element or not, so dp[i] = dp[i-1]*2. To handle the duplicated element, we need to know that which subsequences has been added by a previous A_j = A_i, and I use cnt[A_i] to save those results. The subsequences that has added A_j is dp[j-1]. And we only save the latest dp value because dp is already the prefix sum of dp[1 -> i-1].
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
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
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 123456789;
const int N = 1e6+2;
ll cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(cnt,0,sizeof(cnt));

    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vll dp(n+1);
    dp[0] = 1;

    for(int i = 1; i <= n; i++){
        dp[i] = (dp[i-1]*2 - cnt[a[i]] + MOD)%MOD;
        cnt[a[i]] = dp[i-1];
    }
    cout << (dp[n] - 1 + MOD)%MOD;
}