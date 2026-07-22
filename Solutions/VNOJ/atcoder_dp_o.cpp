/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-22 15:41:16
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Atcoder Educational DP Contest O - Matching 
 *    source: https://oj.vnoi.info/problem/atcoder_dp_o
 *    submission: https://oj.vnoi.info/submission/12804971
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(2^n \cdot n)
 *    metacognition: Let dp[bitmask] as the status of women (who is already connected gets bit 1) -> means the bit 1 of the mask is the processed men ans women so we don't need a second dp status for that. So for each ith man just check if he's good with an unchosen woman and add the result to the next mask
 *    note: DP Bitmask with dp[bitmask] as the status of paired women - we've already have turned on bit in bitmask = paired men number so we don't need a second status. Just check for each ith man and unpaired women states and add them to the next mask
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("atcoder_dp_o.INP", "r")) return;
    freopen("atcoder_dp_o.INP", "r", stdin);
    freopen("atcoder_dp_o.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 21;
const ll MOD = 1e9+7;

bitset<N> is_good[N];
ll dp[1 << N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int x;
            cin >> x;
            is_good[i][j] = x;
        }
    }

    dp[0] = 1;

    for(int mask = 0; mask < (1 << n); mask++){
        int man = __builtin_popcount(mask);
        for(int submask = (~mask) & ((1 << n) - 1); submask; submask &= (submask - 1)){
            int woman = __builtin_ctz(submask);

            ll &nxt_mask = dp[mask | (1 << woman)];
            if(is_good[man][woman]) nxt_mask = (nxt_mask + dp[mask])%MOD;
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