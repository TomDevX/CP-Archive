/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-13 13:44:08
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Chia kẹo 2
 *    source: https://oj.vnoi.info/problem/gogovoi_chiakeo2
 *    submission: https://oj.vnoi.info/submission/12714285
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Inclusion-Exclusion
 *    complexity: O(2^n + n)
 *    metacognition: This is a typical Euler candy problem. But now it has a lower restrictions => Count Euler normally but subtract out the cases which violate the restriction (which is xi > ai), but if we only subtract on each case of violation, it will be wrong because it will overcount some child set cases. So we need to use inclusion-exclusion, we want to first put the chosen elements to violate and then count the cases
 *    note: Use inclusion - exclusion with euler candy counting
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
    if(!fopen("gogovoi_chiakeo2.INP", "r")) return;
    freopen("gogovoi_chiakeo2.INP", "r", stdin);
    freopen("gogovoi_chiakeo2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7, N = 21, M = 1e5+200;

int a[N];
ll fac[M], inv[M];

// ----------------------- [ FUNCTIONS ] -----------------------
ll binpow(ull x, ll k){
    ull res = 1;
    while(k){
        if(k&1) res = (res*x)%MOD;
        x = (x*x)%MOD;
        k >>= 1;
    }
    return res;
}

void precalc(){
    fac[0] = 1;
    for(int i = 1; i < M; i++) fac[i] = (fac[i-1]*i)%MOD;

    inv[M-1] =  binpow(fac[M-1], MOD-2);

    for(int i = M-2; i >= 0; i--){
        inv[i] = (inv[i+1]*(i+1))%MOD;
    }
}

ll nck(ll n, ll k){
    if(k > n) return 0;
    return ((fac[n] * inv[n-k])%MOD)*inv[k]%MOD;
}

ll norm(ll x){
    x %= MOD;
    if(x < 0) x += MOD;
    return x;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int m,n;
    cin >> m >> n;
    for(int i = 0; i < n; i++) cin >> a[i];

    ll ans = nck(m+n-1,n-1);

    for(int mask = 1; mask < (1 << n); mask++){
        ll tot = m + n - 1;
        int cnt = __builtin_popcount(mask);
        for(int submask = mask; submask; submask &= (submask-1)){
            int i = __builtin_ctz(submask);
            tot -= a[i] + 1;
        }

        if(cnt&1) ans = norm(ans - nck(tot, n-1));
        else ans = norm(ans + nck(tot, n-1));
    }

    cout << ans;
}

int main(){
    fastio;
    setup();
    precalc();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}