/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-23 09:14:18
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: product
 *    source: https://oj.vnoi.info/problem/product
 *    submission: https://oj.vnoi.info/submission/11801553
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Two Pointes
 *    complexity: O(n)
 *    note: Instead of getting big num, we use floating point numbers by using log formulas and accept the deviation
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cmath>
#include <string>
#include <algorithm>
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

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ld eps = 1e-7;

// ----------------------- [ FUNCTIONS ] -----------------------
ld to_ld(string s){
    ld res = 0;
    for(int i = sz(s)-1; i >= 0; i--){
        res /= 10;
        res += (s[i] - '0');
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    string s;
    cin >> s;

    ld a = to_ld(s.substr(0,min(15,sz(s))));

    while(a >= 10.0) a/= 10.0;

    long double target = log10(a) + sz(s) -1;
    // dbg(a,1);

    int l = 1;
    ld cur = 0;
    for(int r = 1; r <= 1e5; r++){
        cur += log10(r);
        while(cur > target + eps){
            cur -= log10(l);
            l++;
        }
        if(abs(cur - target) < eps){
            cout << l << ' ' << r;
            return 0;
        }
    }
}
