/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-21 22:43:34
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: To My Critics
 *    source: https://codeforces.com/problemset/problem/1850/A
 *    submission: https://codeforces.com/problemset/submission/1850/363881834
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(t)
 *    note: Just do as the problem said
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
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


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int tc;
    cin >> tc;
    while(tc--){
        int a,b,c;
        cin >> a >> b >> c;
        cout << (max({a,b,c}) + (a+b+c - max({a,b,c}) - min({a,b,c})) >= 10 ? "YES" : "NO") << '\n';
    }
}