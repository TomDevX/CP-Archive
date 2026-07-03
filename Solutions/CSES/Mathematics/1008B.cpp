/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-04 00:28:01
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Turn the Rectangles
 *    source: https://codeforces.com/contest/1008/problem/B
 *    submission: https://codeforces.com/contest/1008/submission/381165532
 *    status: WIACP
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    metacognition: Width and height can be swapped so they have the same roles. Just prioritize the higher width/height for the current block and check
 *    note: Prioritize higher width/height
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
    if(!fopen("1008B.INP", "r")) return;
    freopen("1008B.INP", "r", stdin);
    freopen("1008B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

pii a[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].fi >> a[i].se;
        if(a[i].fi > a[i].se) swap(a[i].fi, a[i].se);
    }

    int cur = 1e9;
    for(int i = 1; i <= n; i++){
        if(a[i].se <= cur) cur = a[i].se;
        else if(a[i].fi <= cur) cur = a[i].fi;
        else{
            cout << "NO";
            return;
        }
    }
    cout << "YES";
}

int main(){
    fastio;
    setup();

    int tc = 1;
    // cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}