/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-26 16:45:56
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tập hợp gần nhau
 *    source: https://oj.vnoi.info/problem/gogovoi_advanced_combin_bai4
 *    submission: https://oj.vnoi.info/submission/12576438
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, BIT
 *    complexity: O(n \log n)
 *    metacognition: Considering the max and min on array is hard => Fix 1 element as max value and count element x which a[i] - k <= x <= a[i] (can count fast using BIT, or two pointers) => Then pick the combinatorics from this
 - Mistakes: Must get (number_of_x)C(m-1), not (number_of_x)C(m) because we've already fix a[i] so we just need to pick another m-1 numbers from it
 *    note: Fix 1 element for every index from 1 -> i (sort the array first to ensure i will always be the max value) => Count satisfy elements (a[i] - k <= x <= a[i]) using BIT or 2 pointer => Get the combinatorics of it from the formula (satisfied elemnts)C(m-1) (m - 1 because already included a[i])
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;
const ll MOD = 1e9+7;

ll fac[N], inv[N];
int bit[N];
int a[N];
int n,m,k;

// ----------------------- [ FUNCTIONS ] -----------------------
ll binpow(ll a, ll k){
    ll res = 1;
    while(k){
        if(k&1) res = (res*a)%MOD;
        a = (a*a)%MOD;
        k>>=1;
    }
    return res;
}

void preprocess(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = (fac[i-1]*i)%MOD;

    inv[N-1] = binpow(fac[N-1], MOD-2);
    for(int i = N-2; i >= 0; i--) inv[i] = (inv[i+1]*(i+1))%MOD;
}

ll getC(int n, int k){
    if(n < 0 || k < 0 || k > n) return 0;
    return ((fac[n]*inv[n-k]%MOD)*inv[k])%MOD;
}

void update(int pos){
    for(; pos <= n; pos += pos&-pos) bit[pos]++;
}

int get(int pos){
    int res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

int query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(sub(a,1,n));

    ll ans = 0;
    for(int i = 1; i <= n; i++){
        int avail = query(max(1,a[i]-k), a[i]);
        ans = (ans+getC(avail,m-1))%MOD;
        update(a[i]);
    }

    cout << ans;
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