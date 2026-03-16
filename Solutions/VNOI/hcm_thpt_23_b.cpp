/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-16 13:06:10
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: HSG THPT TPHCM 2023 - Bắn tàu
 *    source: https://oj.vnoi.info/problem/hcm_thpt_23_b
 *    submission: https://oj.vnoi.info/submission/11890536
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP
 *    complexity: O(n^2 \cdot k)
 *    note: The min cost to fire from range i to j = sum(max(i -> j) - a_x) => cost(i -> j) = max_a*(length) - sum(i -> j). So we can DP on that cost to get the min one. Let dp[i][k] = ends at index k and has changed the range k times. Of course we need to set it always optimal at the beginning
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cstring>

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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 402;
int dp[N][N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;

    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    vi pref(n+1);
    for(int i = 1; i <= n; i++){
        pref[i] = pref[i-1] + a[i];
    }

    vvi cost(n+1, vi(n+1));
    for(int i = 1; i <= n; i++){
        int maxn = a[i];
        for(int j = i; j <= n; j++){
            maxn = max(maxn, a[j]);
            cost[i][j] = maxn*(j-i+1) - (pref[j] - pref[i-1]);
        }
    }

    memset(dp,0x3f,sizeof(dp));
    for(int i = 1; i <= n; i++){
        dp[i][0] = cost[1][i];
    }

    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            for(int z = 1; z <= min(k,i); z++){
                dp[j][z] = min(dp[j][z],dp[i-1][z-1] + cost[i][j]);
            }
        }
    }

    cout << dp[n][k];
    
    return NAH_I_WOULD_WIN;
}