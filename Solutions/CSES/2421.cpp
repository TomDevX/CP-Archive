/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-18 18:43:21
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Counting Reorders
 *    source: https://cses.fi/problemset/task/2421
 *    submission: https://cses.fi/problemset/result/17982326/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP, Inclusion-Exclusion, Math
 *    complexity: O(26 \cdot n^2)
 *    metacognition: 
 *    note: Combine DP with inclusion-exclusion + Stars and Bars (Euler)
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
    if(!fopen("2421.INP", "r")) return;
    freopen("2421.INP", "r", stdin);
    freopen("2421.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int ALPHABET = 27;
const int N = 5002;
const ll MOD = 1e9+7;

struct modll{
    ll val = 0;
    
    modll() : val(0) {};
    modll(ll x) : val(norm(x)) {};
    
    ll norm(ll x) const noexcept {
        x %= MOD;
        if(x < 0) x += MOD;
        return x;
    }
    
    modll binpow(ll k) const noexcept {
        modll res = 1;
        modll x = *this;
        while(k){
            if(k & 1) res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }
    
    // set operators
    void operator +=(modll x) noexcept { val = (val+x.val)%MOD; }
    void operator -=(modll x) noexcept { val = norm(val-x.val); }
    void operator *=(modll x) noexcept { val = (1ULL*val*x.val)%MOD; }
    void operator /=(modll x) noexcept { *this *= x.binpow(MOD-2); }
    
    // operators
    modll operator +(modll x) const noexcept { return  (val + x.val)%MOD; }
    modll operator -(modll x) const noexcept { return norm(val - x.val); }
    modll operator *(modll x) const noexcept { return (1ULL*val * x.val)%MOD; }
    modll operator /(modll x) const noexcept { return *this * x.binpow(MOD-2); }

    // input/output
    friend ostream& operator <<(ostream& os, modll &x) noexcept { return os << x.val; }
    friend istream& operator >>(istream& is, modll &x) noexcept {
        ll inp_val;
        is >> inp_val;
        x = modll(inp_val);
        return is;
    }
};

int cnt_c[ALPHABET];
modll dp[ALPHABET][N];
modll fac[N], inv[N];

// ----------------------- [ FUNCTIONS ] -----------------------
modll binpow(modll x, modll y){
    modll res = 1;
    while(y.val){
        if(y.val&1) res *= x;
        x *= x;
        y.val >>= 1;
    }
    return res;
}

void precalc(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = fac[i-1]*i;

    inv[N-1] = binpow(fac[N-1],MOD-2);
    for(int i = N-2; i >= 0; i--) inv[i] = inv[i+1]*(i+1);
}

modll nck(int n, int k){
    if(k > n) return 0;
    return fac[n]*inv[n-k]*inv[k];
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    string s;
    cin >> s;
    int n = sz(s);
    for(int i = 0; i < n; i++) cnt_c[s[i] - 'a' + 1]++;

    ll processed_char = 0;
    dp[0][0] = 1;

    for(int i = 1; i < ALPHABET; i++){
        if (cnt_c[i] == 0) {
            for (int S = 0; S <= processed_char; S++) dp[i][S] = dp[i-1][S];
            continue;
        }

        for(int S = 0; S <= processed_char; S++){

            for(int sub_j = 1; sub_j <= cnt_c[i]; sub_j++){

                dp[i][S + sub_j] += dp[i-1][S] * ((cnt_c[i] - sub_j) & 1 ? -1LL : 1LL) * nck(cnt_c[i] - 1, sub_j - 1) * nck(S + sub_j, sub_j);

            }

        }
        processed_char += cnt_c[i];
    }

    modll ans = 0;
    for (int T = 1; T <= n; T++) {
        ans += dp[ALPHABET-1][T];
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