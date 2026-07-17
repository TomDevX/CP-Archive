/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-06 22:45:15
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Diện tích hình chữ nhật
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_hinhchunhat
 *    submission: https://oj.vnoi.info/submission/12659816
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Bitmask, Inclusion-Exclusion
 *    complexity: O(2^n)
 *    metacognition: Use inclusion and exclusion on rectangle area. Just try to get their max/min x/y coordinate to calculate the cup value
 *    note: Using inclusion and exclusion to count the cup of rectangle areas
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
    if(!fopen("gogovoi_nangcao_hinhchunhat.INP", "r")) return;
    freopen("gogovoi_nangcao_hinhchunhat.INP", "r", stdin);
    freopen("gogovoi_nangcao_hinhchunhat.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 16;
const int INF = 2e9;

pii x[N], y[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x[i].fi >> y[i].fi >> x[i].se >> y[i].se;
    }    

    ll ans = 0;

    for(int mask = 1; mask < (1 << n); mask++){
        int x_left = -INF, x_right = INF, y_top = INF, y_bottom = -INF;
        for(int i = 0; i < n; i++){
            if(mask >> i & 1){
                x_left = max(x_left, x[i].fi);
                x_right = min(x_right,x[i].se);

                y_top = min(y_top, y[i].se);
                y_bottom = max(y_bottom, y[i].fi);
            }
        }

        if(!(x_right > x_left && y_top > y_bottom)) continue;

        int cnt = __builtin_popcount(mask);
        if(cnt&1){
            ans += 1LL*(x_right-x_left)*(y_top-y_bottom);
        }
        else ans -= 1LL*(x_right-x_left)*(y_top-y_bottom);
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