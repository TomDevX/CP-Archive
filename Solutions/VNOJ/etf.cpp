/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-19 18:03:05
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phi hàm Euler
 *    source: https://oj.vnoi.info/problem/etf
 *    submission: https://oj.vnoi.info/submission/12521263
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log\log n)
 *    note: Normal euler phi
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
    if(!fopen("etf.INP", "r")) return;
    freopen("etf.INP", "r", stdin);
    freopen("etf.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;

int phi[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    for(int i = 1; i < N; i++) phi[i] = i;

    for(int i = 2; i < N; i++){
        if(phi[i] == i){ // phi[i] is prime
            for(int j = i; j < N; j += i){
                phi[j] = phi[j] - phi[j]/i; // (1 - 1/p)
            }
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    cout << phi[n] << '\n';
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