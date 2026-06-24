/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-24 19:08:56
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Divisor Analysis
 *    source: https://cses.fi/problemset/task/2182/
 *    submission: 
 *    status: WIP
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("2182.INP", "r")) return;
    freopen("2182.INP", "r", stdin);
    freopen("2182.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;
const ll MOD = 1e9+7;

pii factors[N];

ll cnt_fac = 0, sum_fac = 0, prod_fac = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
ll norm(ll x){
    x %= MOD;
    if(x < 0) x += MOD;
    return x;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> factors[i].fi >> factors[i].se;
    }

    bool is_even = true;
    for(int i = 1; i <= n; i++){
        cnt_fac = (cnt_fac*(factors[i].se + 1))%MOD;
        sum_fac = (sum_fac*((norm(binpow(factors[i].fi, factors[i].se + 1) - 1)) * binpow(factors[i].fi - 1, MOD-2) % MOD));
        if((factors[i].se + 1) % 2 == 0) is_even = false;
    }

    if(is_even){
        
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