/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-27 14:23:27
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: VOI 23 Bài 4 - Nhà gỗ
 *    source: https://oj.vnoi.info/problem/voi23_whome
 *    submission: https://oj.vnoi.info/submission/12849648
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(2^m * n * m)
 *    metacognition: Such a DP Bitmask problem because M <= 6, so maybe it has the state of dp[n][mask]
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("WHOME.INP", "r")) return;
    freopen("WHOME.INP", "r", stdin);
    freopen("WHOME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2, M = 6;
ll INF;

int a[N], b[M];
ll dp[N][1 << M];
int n,m;
ll P,C;

// ----------------------- [ FUNCTIONS ] -----------------------
ll cost(int l, int r){
    return P - C*(a[r] - a[l])*(a[r] - a[l]);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    memset(dp,-0x3f,sizeof(dp));
    INF = dp[0][0];

    cin >> n >> m >> P >> C;
    for(int i = 1; i <= n; i++) cin >> a[i];

    sort(sub(a,1,n));

    for(int j = 0; j < m; j++) cin >> b[j];

    dp[0][0] = 0;

    for(int i = 0; i < n; i++){
        for(int mask = 0; mask < (1 << m); mask++){
            if(dp[i][mask] == INF) continue;

            dp[i+1][mask] = max(dp[i+1][mask], dp[i][mask]);

            for(int j = 0; j < m; j++){
                if(i + b[j] > n) continue;

                int new_mask = mask | (1 << j);

                dp[i + b[j]][new_mask] = max(dp[i + b[j]][new_mask], dp[i][mask] + cost(i + 1,i + b[j]));
            }
        }
    }

    ll ans = INF;
    int final_mask = (1 << m) - 1;
    for(int i = 1; i <= n; i++){
        ans = max(ans, dp[i][final_mask]);
    }
    cout << ans;
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}