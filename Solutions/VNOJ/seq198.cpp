/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-25 16:36:11
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: VOI 16 Bài 1 - SEQ198
 *    source: https://oj.vnoi.info/problem/seq198
 *    submission: https://oj.vnoi.info/submission/12834930
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(2^10 \cdot n)
 *    metacognition: Thought about greedy to remove the ones that have more in-degree nodes (violate nodes will be connected together on graph). But there's are some cases we need to remove the some other in-degree nodes but not the highest one to obtain the best approach -> Notice the difference only have the range of 1 -> 9 (1,8,9), so we can do DP Bitmask with the Bitmask on the available a[i] - x => check if there's any bit turned on at (1,8,9).
 *    note: Use DP Bitmask with dp[n][mask] = max keepable values in 1 -> n. bit k of mask is on means there's ith element - k.
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
    if(!fopen("seq198.INP", "r")) return;
    freopen("seq198.INP", "r", stdin);
    freopen("seq198.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2002;

int a[N];
int dp[N][1 << 10];

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int mask){
    return !(mask >> 1 & 1 || mask >> 8 & 1 || mask >> 9 & 1);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(sub(a,1,n));

    for(int i = 0; i < n; i++){
        for(int mask = 0; mask < (1 << 10); mask++){
            // not choose
            int new_mask = (a[i+1] - a[i] > 9 ? 0 : (mask << (a[i+1] - a[i])) & ((1 << 10) - 1));
            dp[i+1][new_mask] = max(dp[i+1][new_mask], dp[i][mask]);

            // choose
            if(!check(new_mask)) continue;
            new_mask = new_mask | 1;
            dp[i+1][new_mask] = max(dp[i+1][new_mask], dp[i][mask] + 1);
        }
    }

    int ans = 0;
    for(int mask = 0; mask < (1 << 10); mask++){
        ans = max(ans, dp[n][mask]);
    }
    cout << n-ans;
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