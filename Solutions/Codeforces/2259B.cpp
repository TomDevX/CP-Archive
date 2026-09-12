/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-09-12 22:17:41
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Minus Two
 *    source: https://codeforces.com/contest/2259/problem/B
 *    submission: https://codeforces.com/contest/2259/submission/390457030
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy, Implementation, Math
 *    complexity: O(n)
 *    metacognition: Maybe we can divide them into 2 groups as "x % 2 == 1" and "x % 2 == 0" and they can be compared together? >< there's another group which is "x % 4 == 0" and it will never matches with the ones that are only "x % 2 == 0"
 *    note: Divide numbers into 2 groups: "x % 2 == 1", only "x % 2 == 0", and "x % 4 == 0" and get the max out of them
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
    if(!fopen("2259B.INP", "r")) return;
    freopen("2259B.INP", "r", stdin);
    freopen("2259B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int cnt1 = 0;
    for(int i = 1; i <= n; i++) cnt1 += (a[i] % 2);

    int cnt4 = 0;
    for(int i = 1; i <= n; i++) cnt4 += (a[i] % 4 == 0);

    int cnt2 = 0;
    for(int i = 1; i <= n; i++) cnt2 += (a[i] % 2 == 0);
    cnt2 -= cnt4;

    cout << max({cnt1,cnt2,cnt4}) << '\n';
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