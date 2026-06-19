/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-19 15:30:39
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: The Number of Pairs
 *    source: https://codeforces.com/contest/1499/problem/D
 *    submission: https://codeforces.com/contest/1499/submission/379473057
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(\sqrt{n} + n \log\log n)
 *    note: We have the formula here: c*lcm(a,b) - d*gcd(a,b) = x
 1. Let gcd(a,b) = g => a = g*p | b = g*q => lcm(a,b) = a*b/gcd(a,b) = g^2*p*q/g = g*p*q
 2. Our formula turn into c*g*p*q + d*g = x => g(c*p*q - d) = x => g is a divisor of x => p*q = ((x/g) + d)/c
 3. Let K = ((x/g) + d)/c | So that, we just need to count total number of K's divisors which match the following conditions:
    a. p*q = K
    b. gcd(p,q) = 1
 4. We already have p*q = K, now we need to consider the case gcd(p,q) = 1 -> Each p and q must be a separate sequence of prime factors, which means we have total of 2^{number of K's prime factors} ways to make p and q
 5. To make our program faster, we can precompute number of prime_factor for each number using sieve and precompute pow2 (only <= log2(2e7))
 6. since our numerator is (x/g) + d so maybe it will reach maximum of 2e7, so we need to set lim = 2e7 instead of 1e7
 7. In the main program, we just iterate through all divisors O(\sqrt{n}) and add the formula's result to answer
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("1499D.INP", "r")) return;
    freopen("1499D.INP", "r", stdin);
    freopen("1499D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e7+5;

int cnt_fac[N];
int pow2[26];

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    for(int i = 2; i < N; i++){
        if(!cnt_fac[i]){
            for(int j = i; j < N; j += i){
                cnt_fac[j]++;
            }
        }
    }

    pow2[0] = 1;
    for(int i = 1; i < 26; i++) pow2[i] = pow2[i-1] << 1;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int c,d,x;
    cin >> c >> d >> x;

    ll ans = 0;

    for(int g = 1; g * g <= x; g++){
        if(x%g != 0) continue;

        if((g + d)%c == 0){
            int K = (g + d)/c;
            ans += pow2[cnt_fac[K]];
        }

        int g2 = x/g;
        if(g == g2) continue;

        if((g2 + d)%c == 0){
            int K = (g2 + d)/c;
            ans += pow2[cnt_fac[K]];
        }
    }

    cout << ans << '\n';    
}

int main(){
    fastio;
    setup();
    sieve();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}