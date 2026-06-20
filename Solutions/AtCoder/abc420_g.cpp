/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-19 17:09:30
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: sqrt(n²+n+X)
 *    source: https://atcoder.jp/contests/abc420/tasks/abc420_g
 *    submission: https://atcoder.jp/contests/abc420/submissions/76789480
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(\sqrt{X})
 *    note: We need to have some formula shifting here:
 1. Let \sqrt{n^2 + n + X} = m => n^2 + n + X = m^2 => 4n^2 + 4n + 4X = 4m^2 => (2n + 1)^2 - 1 + 4X = 4m^2 (Force to be a quadratic with 4n^2 + 4n + 1 = (2n + 1)^2, so we +1 and -1)
 2. We have A^2 - B^2 = (A - B)(A + B) (identity) => (2n + 1 - 2m)(2n + 1 + 2m) = 1 - 4X
 3. Let d = 2n + 1 + 2m and C = 1 - 4X => 2n + 1 - 2m = C/d
 4. We have 2n + 1 - 2m + 2n + 1 + 2m = C/d + d => 4n + 2 = C/d + d => n = (C/d + d - 2)/4 (1)
 5. Finally, we just need to iterate 1 -> \sqrt{X} to find all d and then => value of n with formula 1
 Note: Since n can be negative so d can be negative so we need to add(-d) too
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("abc420_g.INP", "r")) return;
    freopen("abc420_g.INP", "r", stdin);
    freopen("abc420_g.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
vll ans;
ll C;

// ----------------------- [ FUNCTIONS ] -----------------------
void add(ll d){
    ll ele = (C/d + d - 2)/4;
    ans.eb(ele);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll x;
    cin >> x;

    C = 1-4*x;

    ll V = abs(C);

    for(ll d = 1; d * d <= V; d++){
        if(V%d != 0) continue;

        add(d);
        add(-d);
    }

    sort(all(ans,0));

    cout << sz(ans) << '\n';
    for(ll i : ans) cout << i << ' ';
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