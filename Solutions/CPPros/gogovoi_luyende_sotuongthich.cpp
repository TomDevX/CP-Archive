/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-28 19:02:21
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Số tương thích
 *    source: https://oj.vnoi.info/problem/gogovoi_luyende_sotuongthich
 *    submission: https://oj.vnoi.info/src/12861544
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask, DP SOS
 *    complexity: O(2^n \cdot n)
 *    metacognition: x & y = 0 means that y must be a submask of ~x. So to check mask fast we use DP Bitmask with dp[mask] as max number available in submasks of mask. To calculate this fast, we need to calculate mask from small to large so when we retrieve for current mask just disable its 1 bits. Answer = dp[~x]
 *    note: dp[mask] = max number available in array as submasks of mask, because when x & y = 0 => y = submask ~x. To calculate fast we process mask from small to large to when we retrieve the value for current mask just need to disable the bit 1s sequentially
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
    if(!fopen("gogovoi_luyende_sotuongthich.INP", "r")) return;
    freopen("gogovoi_luyende_sotuongthich.INP", "r", stdin);
    freopen("gogovoi_luyende_sotuongthich.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = (1 << 20) + 5, M = 1e6+5;

int dp[N];
int a[M];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    memset(dp,-1,sizeof(dp));

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        dp[a[i]] = a[i];
    }

    for(int mask = 1; mask < (1 << 20); mask++){
        for(int i = 0; i < 20; i++){
            if(mask >> i & 1){
                dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        cout << dp[(~a[i]) & ((1 << 20) - 1)] << ' ';
    }
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
