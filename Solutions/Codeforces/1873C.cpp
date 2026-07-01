/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-02 00:06:07
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Target Practice
 *    source: https://codeforces.com/contest/1873/problem/C
 *    submission: https://codeforces.com/contest/1873/submission/380942954
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(10^2)
 *    metacognition: Instead of considering the column or rows, we notice that the min value is what matters
 *    note: Focus on the min value of cols, its opposite and rows with its opposite
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
    if(!fopen("1873C.INP", "r")) return;
    freopen("1873C.INP", "r", stdin);
    freopen("1873C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 10;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    char c;
    int ans = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> c;
            if(c == 'X'){
                ans += min({i, j, 10 - i + 1, 10 - j + 1});
            }
        }
    }
    cout << ans << '\n';    
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}