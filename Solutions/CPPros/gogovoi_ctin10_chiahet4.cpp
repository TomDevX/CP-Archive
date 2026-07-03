/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-02 21:23:12
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: [Trung Bình] Chia hết 4, 7, 11
 *    source: https://oj.vnoi.info/problem/gogovoi_ctin10_chiahet4
 *    submission: https://oj.vnoi.info/submission/12635136
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Inclusion-Exclusion, Bitmask
 *    complexity: O(2 ^ 3)
 *    metacognition: Inclusion-Exclusion problem
 *    note: Just do the inclusion - exclusion problem, odd elements is +, and even elements is -. Remember that l-1 maybe -1 so we need to consider that case carefully
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
    if(!fopen("gogovoi_ctin10_chiahet4.INP", "r")) return;
    freopen("gogovoi_ctin10_chiahet4.INP", "r", stdin);
    freopen("gogovoi_ctin10_chiahet4.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int target[3] = {4,7,11};

int gcd(int a, int b){
    while(b){
        int tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

int lcm(int a, int b){
    return a*b/gcd(a,b);
}

// ----------------------- [ FUNCTIONS ] -----------------------
ll solve(ll n){
    ll res = 0;
    for(int mask = 1; mask < (1 << 3); mask++){
        int cur = 1;
        for(int j = 0; j < 3; j++){
            if(mask >> j & 1) cur = lcm(cur, target[j]);
        }
        if(__builtin_popcount(mask) & 1) res += n/cur + 1;
        else res -= n/cur + 1;
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll l,r;
    cin >> l >> r;
    cout << solve(r) - (l-1 < 0 ? 0 : solve(l-1)) << '\n';
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