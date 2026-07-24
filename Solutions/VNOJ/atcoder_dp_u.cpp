/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-24 18:08:16
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Atcoder Educational DP Contest U - Grouping
 *    source: https://oj.vnoi.info/problem/atcoder_dp_u
 *    submission: https://oj.vnoi.info/submission/12827007
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask, Iterate Submask
 *    complexity: O(2^n \cdot n^2 + 3^n)
 *    metacognition: Use DP Bitmask with dp[mask] as best cost for chosen set of rabbits. So we need to iterate 2 mask, consider submask as a whole new group => dp[mask] = best(dp[mask \ submask] + cost[submask]) = best(dp[mask \ submask] + dp[submask]) (if initialize all dp as its whole group cost). To calculate the cost quickly, we need to pre calculate it in O(2^n * n^2)
 *    note: dp[mask] as best cost for chosen set of rabits. Use 2 iterations dp[mask] = best(dp[mask \ submask] + cost[submask]). Need to precalc cost for faster dp count
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
    if(!fopen("atcoder_dp_u.INP", "r")) return;
    freopen("atcoder_dp_u.INP", "r", stdin);
    freopen("atcoder_dp_u.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 16;

int a[N][N];
ll cost[1 << N];
ll dp[1 << N];
vi cur;
int backtrack_mask = 0;

int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void calculate_cost(int idx){
    if(idx == n){
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(backtrack_mask >> i & 1 && backtrack_mask >> j & 1) cost[backtrack_mask] += a[i][j];
            }
        }
        return;
    }

    calculate_cost(idx+1);
    backtrack_mask |= (1 << idx);
    calculate_cost(idx+1);  
    backtrack_mask ^= (1 << idx);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cin >> a[i][j];
    }

    calculate_cost(0);
    dp[0] = 0;

    for(int mask = 1; mask < (1 << n); mask++){
        dp[mask] = cost[mask];

        for(int submask = mask; submask; submask = mask & (submask - 1)){
            dp[mask] = max(dp[mask], dp[mask ^ submask] + cost[submask]);
        }
    }

    cout << dp[(1 << n) - 1];
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