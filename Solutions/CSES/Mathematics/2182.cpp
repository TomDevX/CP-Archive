/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-24 19:08:56
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Divisor Analysis
 *    source: https://cses.fi/problemset/task/2182/
 *    submission: https://cses.fi/problemset/result/17688457/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log k)
 *    metacognition: We already know the formula of getting cnt of divisors, sum of divisors and product of divisors through prime factors so it must be easy -> But how about the product of divisors which have formula of n^(cnt/2)? It will have a div 2 right there and we need to consider the cases -> if cnt (not modulo) is even => We can easily divide it (but we need to find 1 even number in it and divide it by 2 before contributing to cnt because cnt is already modulo and we cant divide on modulo with a %(MOD-1) for the exponential) | we know that n is contribution of its fac and each's exponential => if cnt is odd number, it means that the all original exponential is even => we can divide their original value by 2 and add it through prod of factors to make n^(cnt/2) through its factors
 *    note: It is easy for the cnt and sum. But for product, we can't divide 2 easily (n^(cnt/2)). If cnt is even, we just need to find 1 contributor (factor + 1) which is even and divide it and count n^cnt | If cnt = odd, means that all original factors are even (because there's no even in (factors + 1)) => n^(cnt/2) = (p1^a1 * p2^a2 * ... * p3^ak)^(cnt/2) = p1^(a1*cnt/2) * p2^(a2*cnt/2) * ... * pk^(ak*cnt/2) - because a1,a2,...,ak has original value so we can divide by 2 normally. (Notice: For the exponential modulo, it must be MOD-1 because of Fermat's Little Theorem or phi rule of modulo)
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

ll cnt_fac = 1, sum_fac = 1, prod_fac = 1;

// ----------------------- [ FUNCTIONS ] -----------------------
ll norm(ll x){
    x %= MOD;
    if(x < 0) x += MOD;
    return x;
}

ll binpow(ll a, ll k){
    ll res = 1;
    while(k){
        if(k&1) res = (res*a)%MOD;
        a = (a*a)%MOD;
        k >>= 1;
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> factors[i].fi >> factors[i].se;
    }

    bool is_even = false;
    for(int i = 1; i <= n; i++){
        cnt_fac = (cnt_fac*(factors[i].se + 1))%MOD;
        sum_fac = (sum_fac*((norm(binpow(factors[i].fi, factors[i].se + 1) - 1)) * binpow(factors[i].fi - 1, MOD-2) % MOD))%MOD;
        if((factors[i].se + 1) % 2 == 0) is_even = true;
    }

    ll cnt = 1;
    for(int i = 1; i <= n; i++){
        cnt = (cnt*(factors[i].se + 1))%(MOD-1);
    }

    if(is_even){
        bool is_div = false;
        ll mu = 1, x = 1;
        
        for(int i = 1; i <= n; i++){
            if(!is_div && (factors[i].se + 1)%2 == 0){
                mu = (mu * ((factors[i].se + 1)>>1))%(MOD-1);
                is_div = true;
            }
            else mu = (mu * (factors[i].se + 1))%(MOD-1);

            x = (x * binpow(factors[i].fi, factors[i].se))%MOD;
        }

        prod_fac = binpow(x,mu);
    }
    else{
        for(int i = 1; i <= n; i++){
            ll new_fac = binpow(factors[i].fi, ((factors[i].se>>1)*cnt)%(MOD-1));
            prod_fac = (prod_fac*new_fac)%MOD;
        }
    }

    cout << cnt_fac << ' ' << sum_fac << ' ' << prod_fac;
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