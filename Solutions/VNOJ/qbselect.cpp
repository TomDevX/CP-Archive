/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-08-01 18:22:28
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: VOI 06 Bài 1 - Chọn ô
 *    source: https://oj.vnoi.info/problem/qbselect
 *    submission: https://oj.vnoi.info/src/12905813
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O(m \cdot 2^n \cdot 2^n)
 *    metacognition: 
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
    if(!fopen("qbselect.INP", "r")) return;
    freopen("qbselect.INP", "r", stdin);
    freopen("qbselect.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1 << 4, M = 1e4+5;

ll dp[2][N];
ll sum[M][N];
int a[4][M];
int n = 4,m;

// ----------------------- [ FUNCTIONS ] -----------------------
void rest(int id){
    memset(dp[id], -0x3f, sizeof(dp[id]));
}

bool check(int mask1, int mask2){
    for(int i = 0; i < n; i++){
        if(mask1 >> i & 1 && mask2 >> i & 1) return false;
        if(mask1 >> i & 1 && (mask1 >> (i + 1) & 1 || (i - 1 >= 0 ? mask1 >> (i-1) & 1 : 0))) return false;
        if(mask2 >> i & 1 && (mask2 >> (i + 1) & 1 || (i - 1 >= 0 ? mask2 >> (i-1) & 1 : 0))) return false;
    }
    return true;
}

ll get_sum(int mask, int col){
    ll sum = 0;
    for(int i = 0; i < n; i++){
        if(mask >> i & 1) sum += a[i][col];
    }
    return sum;
}

void precalc(){
    for(int j = 0; j < m; j++){
        for(int mask = 1; mask < (1 << n); mask++){
            sum[j][mask] = get_sum(mask, j);
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> m;

    int maxele = -1e9;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) cin >> a[i][j], maxele = max(maxele, a[i][j]);
    }
    precalc();
    rest(0);
    
    for(int mask = 0; mask < (1 << n); mask++){
        if(check(mask,0)){
            dp[0][mask] = get_sum(mask, 0);
        }
    }

    for(int j = 1; j < m; j++){
        rest(1);
        for(int mask = 0; mask < (1 << n); mask++){
            for(int nxt_mask = 0; nxt_mask < (1 << n); nxt_mask++){
                if(!check(mask,nxt_mask)) continue;

                dp[1][nxt_mask] = max(dp[1][nxt_mask], dp[0][mask] + sum[j][nxt_mask]);
            }  
        }
        swap(dp[0], dp[1]);
    }

    ll ans = 0;
    for(int mask = 0; mask < (1 << n); mask++){
        ans = max(ans, dp[0][mask]);
    }
    cout << (ans == 0 ? maxele : ans);
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
