/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-22 16:40:10
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: The problem for kid
 *    source: https://oj.vnoi.info/problem/maugiao
 *    submission: https://oj.vnoi.info/submission/12805952
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(2^n * n)
 *    metacognition: Just like Solutions/VNOJ/atcoder_dp_o but with counting => which meets the right maximum value we count it with another cnt[mask]
 *    note: Check out Solutions/VNOJ/atcoder_dp_o and combine it with counting ways to get the max value if it meets the true max valueu
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

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
    if(!fopen("maugiao.INP", "r")) return;
    freopen("maugiao.INP", "r", stdin);
    freopen("maugiao.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 20;

ll dp[1 << N], cnt[1 << N];
int val[N][N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cin >> val[i][j];
    }

    cnt[0] = 1;

    for(int mask = 0; mask < (1 << n); mask++){
        int SON = __builtin_popcount(mask);

        for(int submask = (~mask) & ((1 << n) - 1); submask; submask &= (submask - 1)){
            int DAWG = __builtin_ctz(submask);

            int nxt_mask = mask | (1 << DAWG);

            ll new_val = dp[mask] + val[SON][DAWG];

            if(dp[nxt_mask] < new_val){
                dp[nxt_mask] = new_val;
                cnt[nxt_mask] = cnt[mask];
            }
            else if(dp[nxt_mask] == new_val){
                cnt[nxt_mask] += cnt[mask];
            }
        }
    }

    int final_mask = (1 << n) - 1;
    cout << dp[final_mask] << ' ' << cnt[final_mask];
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