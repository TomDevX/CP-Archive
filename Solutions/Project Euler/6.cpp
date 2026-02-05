/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-06 00:45:43
 *    country: Vietnam - VNM
 *    title: Sum Square Difference
 *    source: https://projecteuler.net/problem=6
 *    submission: 
 * ----------------------------------------------------------
 *    tags: Level 0
 *    complexity: O(1)
 *    note: Use normal math formulas. By the way, there's a fun fact that (1+2+...+n)^2 = 1^3 + 2^3 + 3^3 + ... + n^3
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    ull n = 100;
    cout << (n*(n+1)>>1)*(n*(n+1)>>1) - (n*(n+1)*(2*n+1))/6;
}