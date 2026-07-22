/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-19 18:31:03
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Đàn bò hỗn loạn
 *    source: https://oj.vnoi.info/problem/mixup2
 *    submission: https://oj.vnoi.info/submission/12774354
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
#include <cmath>

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
    if(!fopen("mixup2.INP", "r")) return;
    freopen("mixup2.INP", "r", stdin);
    freopen("mixup2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 16;

ll dp[1 << N][N];
int val[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n, K;
    cin >> n >> K;
    for(int i = 0; i < n; i++) cin >> val[i];

    for(int i = 0; i < n; i++) dp[1 << i][i] = 1;

    for(int mask = 1; mask < (1 << n); mask++){
        for(int submask1 = mask; submask1; submask1 &= (submask1-1)){
            int cur = __builtin_ctz(submask1);
            if(dp[mask][cur] == 0) continue;

            for(int submask0 = (~mask) & ((1 << n) - 1); submask0; submask0 &= (submask0 - 1)){
                int nxt = __builtin_ctz(submask0);
                if(abs(val[nxt] - val[cur]) <= K) continue;

                dp[mask | (1 << nxt)][nxt] += dp[mask][cur];
            }
        }
    }

    ll ans = 0;
    int final_mask = (1 << n) - 1;
    for(int cur = 0; cur < n; cur++){
        ans += dp[final_mask][cur];
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