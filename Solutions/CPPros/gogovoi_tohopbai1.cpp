/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-26 21:39:59
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tạo xâu II
 *    source: https://oj.vnoi.info/problem/gogovoi_tohopbai1
 *    submission: https://oj.vnoi.info/submission/12578465
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(|S|)
 *    metacognition: Permutation with repetition
 *    note: Permuation with repetition. Preprocess inversion with O(n)
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
    if(!fopen("gogovoi_tohopbai1.INP", "r")) return;
    freopen("gogovoi_tohopbai1.INP", "r", stdin);
    freopen("gogovoi_tohopbai1.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int ALPHABET = 27, N = 1e6+5;
const ll MOD = 1e9+7;

int cnt[ALPHABET];
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

void preprocess(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = (fac[i-1]*i)%MOD;

    inv[N-1] = binpow(fac[N-1],MOD-2);
    for(int i = N-2; i >= 0; i--) inv[i] = (inv[i+1]*(i+1))%MOD;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    string s;
    cin >> s;

    int n = sz(s);

    for(int i = 0; i < n; i++){
        cnt[s[i] - 'a']++;
    }

    ll mau = 1;
    for(int i = 0; i < 26; i++){
        if(cnt[i] > 1) mau = (mau*inv[cnt[i]])%MOD;
    }

    cout << (fac[n]*mau)%MOD;
}

int main(){
    fastio;
    setup();
    preprocess();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}