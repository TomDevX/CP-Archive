/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-09 10:35:27
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Orac and LCM
 *    source: https://codeforces.com/contest/1349/problem/A
 *    submission: https://codeforces.com/contest/1349/submission/377986037
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log \text{max}(n))
 *    note: Just draw out the gcd of all LCMs with small tests and we can see some math observations below
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>

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
    if(!fopen("1349A.INP", "r")) return;
    freopen("1349A.INP", "r", stdin);
    freopen("1349A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int a[N];
int sang[N];
vi mu[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    iota(all(sang,2),2);
    for(int i = 2; i * i < N; i++){
        if(sang[i] != i) continue;
        for(int j = i * i; j < N; j += i) sang[j] = i;
    }
}

void phantich(int n){
    while(n > 1){
        int p = sang[n];

        int cnt = 0;

        while(n%p == 0){
            cnt++;
            n /= p;
        }

        mu[p].eb(cnt);
    }
}

ll binpow(ll a, int k){
    ll res = 1;
    while(k){
        if(k&1) res *= a;
        a *= a;
        k >>= 1;
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    sieve();
    int n;
    cin >> n;

    for(int i = 1, x; i <= n; i++){
        cin >> x;
        phantich(x);
    }

    ll ans = 1;
    for(int i = 2; i < N; i++){
        if(sz(mu[i])){
            sort(all(mu[i],0));
            int mu_size = sz(mu[i]);

            int tot = mu_size;
            if(mu_size == n){ // if all numbers contain the factor, the gcd will be the second smallest
                ans *= binpow(i,mu[i][1]);
            }
            else if(mu_size == n-1) ans *= binpow(i, mu[i][0]); // if only 1 number doesn't contain this factor, gcd will be the smallest
        }
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