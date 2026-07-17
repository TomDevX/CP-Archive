/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-30 17:09:41
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bracket Sequences I
 *    source: https://cses.fi/problemset/task/2064
 *    submission: https://cses.fi/problemset/result/17761466/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Catalan
 *    complexity: O(n)
 *    metacognition: Oh it's catalan number
 *    note: Do factorial and inversion for Combinatorics and count Catalan
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
    #define dbg(x)
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
    if(!fopen("2064.INP", "r")) return;
    freopen("2064.INP", "r", stdin);
    freopen("2064.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;
const ll MOD = 1e9+7;

ll fac[N], inv[N];

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

void precalc(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = (fac[i-1]*i)%MOD;

    inv[N-1] = binpow(fac[N-1], MOD-2);

    for(int i = N-2; i >= 0; i--) inv[i] = (inv[i+1]*(i+1))%MOD;
}

ll Cnk(int n, int k){
    if(n < 0 || k < 0 || k > n) return 0;
    return (fac[n]*inv[n-k])%MOD*inv[k]%MOD;
}

ll norm(ll x){
    x %= MOD;
    if(x < 0) x += MOD;
    return x;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    if(n&1){
        cout << 0;
        return;
    }

    cout << norm(Cnk(n, (n >> 1)) - Cnk(n, (n >> 1) -1));
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