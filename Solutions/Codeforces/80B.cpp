/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-24 23:50:05
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Depression
 *    source: https://codeforces.com/contest/80/problem/B
 *    submission: https://codeforces.com/contest/80/submission/380043192
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(1)
 *    metacognition: Hmm now we just need to calculate per hour degree on the clock (and what we need), and then per minute degree in 1 hour on the clock
 *    note: 1 minute degree = 360/60 = 6 degree. 1 hour degree = 360/12 = 30 degree. 1 minute on minute hand = 1/60 * (1 hour degree) on hour hand. So our formula for:
 - minute: minute*(1 minute degree)
 - hour: hour*(1 hour degree) + minute*(1 minute on minute hand)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <iomanip>

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
    if(!fopen("80B.INP", "r")) return;
    freopen("80B.INP", "r", stdin);
    freopen("80B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    string s;
    cin >> s;

    int h = ((s[0] - '0')*10 + (s[1] - '0'))%12;
    int m = ((s[3] - '0')*10 + (s[4] - '0'));

    double m_deg = (360.0/60.0)*m;
    double h_deg = (360.0/12.0)*h + (m_deg/360.0)*(360.0/12.0);

    cout << fixed << setprecision(9) << h_deg << ' ' << m_deg;

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