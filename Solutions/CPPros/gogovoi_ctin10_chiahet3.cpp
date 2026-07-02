/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-02 20:55:45
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: [Cơ bản] Chia hết 4 hoặc 10
 *    source: https://oj.vnoi.info/problem/gogovoi_ctin10_chiahet3
 *    submission: https://oj.vnoi.info/submission/12625260
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Inclusion-Exclusion
 *    complexity: O(1)
 *    metacognition: Just use inclusion as |A intersect B| = |A| + |B| - |A union B|
 *    note: Use inclusion-exclusion
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
    if(!fopen("gogovoi_ctin10_chiahet3.INP", "r")) return;
    freopen("gogovoi_ctin10_chiahet3.INP", "r", stdin);
    freopen("gogovoi_ctin10_chiahet3.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
ll solve(ll n, ll x){
    return n / x;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll l,r;
    cin >> l >> r;
    cout << solve(r,4) + solve(r,10) - solve(r, 20) - (solve(l-1,4)  + solve(l-1,10) - solve(l-1,20));
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