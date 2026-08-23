/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-08-10 16:04:24
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Đảo ngược
 *    source: https://oj.vnoi.info/problem/gogovoi_luyende_reverse
 *    submission: https://oj.vnoi.info/submission/13000859
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
 *    note:     
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
    if(!fopen("gogovoi_luyende_reverse.INP", "r")) return;
    freopen("gogovoi_luyende_reverse.INP", "r", stdin);
    freopen("gogovoi_luyende_reverse.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 20;

int dp[1 << N];

// ----------------------- [ FUNCTIONS ] -----------------------
void turn_bit_on(int bit, int &mask){
    mask |= (1 << bit);
}

void turn_bit_off(int bit, int &mask){
    mask &= ~(1 << bit);
}

bool is_on(int bit, int mask){
    return mask >> bit & 1;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    string s;
    cin >> s;
    int n = sz(s);

    int l = 0;
    int avail = 0;

    // initial value for DP
    for(int i = 0; i < n; i++){
        while(is_on(s[i] - 'a', avail)){
            turn_bit_off(s[l] - 'a', avail);
            l++;
        }
        turn_bit_on(s[i] - 'a', avail);
        dp[avail] = __builtin_popcount(avail);
    }

    // setup DP
    // downwards
    for(int i = 0; i < N; i++){
        for(int mask = (1 << N) - 1; mask; mask--){
            if(mask >> i & 1) dp[mask ^ (1 << i)] = max(dp[mask ^ (1 << i)], dp[mask] - 1);
        }
    }

    // upwards
    for(int i = 0; i < N; i++){
        for(int mask = 0; mask < (1 << N); mask++){
            if(mask >> i & 1) dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
        }
    }

    // get result
    int ans = 0;
    for(int mask = 0; mask < (1 << N); mask++){
        ans = max(ans, dp[mask] + dp[((1 << N) - 1) ^ mask]);
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