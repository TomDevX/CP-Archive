/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-14 23:24:37
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Sum of Divisors
 *    source: https://cses.fi/problemset/task/1082
 *    submission: https://cses.fi/problemset/result/17568179/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(\sqrt{n})
 *    note: We have a formula that sum(i = 1 - > n){i * (n/i)} is the answer (count each number contribution to the sum as a divider from 1 -> n). Notice that n/i will keep being the same value and divide i into groups with same value. So we can transform the same group (which has same n/i) to q * sum(i -> x) with q = n/i and x = max value so that n/x = q. In order to find x, we have floor(n/x) = q => x <= floor(n/q) so floor(n/q) will be max x
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
    if(!fopen("1082.INP", "r")) return;
    freopen("1082.INP", "r", stdin);
    freopen("1082.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7;

// ----------------------- [ FUNCTIONS ] -----------------------
ll binpow(ll a, ll k){
    ll res = 1;
    while(k){
        if(k&1) res = (res*a)%MOD;
        a = (a*a)%MOD;
        k >>= 1;
    }
    return res;
}

ll divide(ll tu, ll mau){
    return (tu * binpow(mau,MOD-2))%MOD;
}

ll get_sum(ll l, ll r){
    ll tu = (((l + r)%MOD)*((r-l+1)%MOD))%MOD;
    ll mau = 2;
    return divide(tu,mau);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll n;
    cin >> n;

    ll ans = 0;

    for(ll l = 1, r; l <= n; l = r + 1){
        ll q = n/l;
        r = n/q;
        
        ans = (ans + (q*get_sum(l, r))%MOD)%MOD;
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