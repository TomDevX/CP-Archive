/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-13 14:04:06
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Restricted equation 2 
 *    source: https://marisaoj.com/problem/622
 *    submission: https://marisaoj.com/submission/1290213
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Inclusion-Exclusion
 *    complexity: O(n + S)
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
    if(!fopen("622.INP", "r")) return;
    freopen("622.INP", "r", stdin);
    freopen("622.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7, M = 4e6+5;

ull fac[M], inv[M];

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
    if(k > n || n < 0 || k < 0) return 0;
    return ((fac[n] * inv[n-k])%MOD)*inv[k]%MOD;
}

ll norm(ll x){
    x %= MOD;
    if(x < 0) x += MOD;
    return x;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    ll S,n,L,H;
    cin >> S >> n >> L >> H;

    ll ans = nck(S-L*n + n - 1, n-1);

    for(int k = 1; k <= n; k++){
        ll new_lim = S - L*n - (H-L+1)*k;
        if(new_lim < 0) continue;

        ll ways = nck(n,k)*nck(new_lim + n - 1, n - 1)%MOD;

        if(k&1){
            ans = norm(ans - ways);
        }
        else{
            ans = norm(ans + ways);
        }
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