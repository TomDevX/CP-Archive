/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-18 21:13:26
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Cô gái chăn bò
 *    source: https://oj.vnoi.info/problem/cowgirl
 *    submission: https://oj.vnoi.info/submission/12773363
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask
 *    complexity: O((2^{\text{min}(n,m)})^2 * \text{max}(n,m))
 *    metacognition: Use DP Bitmask on the min(n,m) (they'll be <= 5) and iterate through the max(n,m) side and make 2 bitmasks and check if they are valid for the problem's condition and accumulate the result. We need to choose the min(n,m) because 2^n can be very large so it can kill us on some test like (30,1)
 *    note: Use DP Bitmask with the bitmask status of min(n,m). Iterate through max(n,m) and check the problem's condition
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
    if(!fopen("cowgirl.INP", "r")) return;
    freopen("cowgirl.INP", "r", stdin);
    freopen("cowgirl.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 10;

ll dp[2][1 << N];

// ----------------------- [ FUNCTIONS ] -----------------------
void rest(int n, int id){
    for(int mask = 0; mask < (1 << n); mask++){
        dp[id][mask] = 0;
    }
}

bool get_bit(int mask, int idx){
    return mask >> idx & 1;
}

bool check(int n, int mask1, int mask2){
    for(int i = 0; i < n-1; i++){
        if((get_bit(mask1,i) & get_bit(mask1, i + 1) & get_bit(mask2,i) & get_bit(mask2,i+1)) || (!get_bit(mask1,i) & !get_bit(mask1, i + 1) & !get_bit(mask2,i) & !get_bit(mask2,i+1))) return false;
    }
    return true;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,m;
    cin >> n >> m;
    if(n > m) swap(n,m);

    for(int mask = 0; mask < (1 << n); mask++){
        dp[0][mask] = 1;
    }
    
    for(int i = 2; i <= m; i++){
        rest(n,1);
        for(int mask = 0; mask < (1 << n); mask++){
            if(dp[0][mask] == 0) continue;

            for(int mask_nxt = 0; mask_nxt < (1 << n); mask_nxt++){
                if(check(n, mask, mask_nxt)) dp[1][mask_nxt] += dp[0][mask];
            }
        }
        swap(dp[0], dp[1]);
    }

    ll ans = 0;
    for(int mask = 0; mask < (1 << n); mask++){
        ans += dp[0][mask];
    }
    cout << ans << '\n';

    rest(n,0);
    rest(n,1);
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}