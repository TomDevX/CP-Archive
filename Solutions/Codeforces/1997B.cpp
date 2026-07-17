/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-02 00:42:41
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Make Three Regions
 *    source: https://codeforces.com/contest/1997/problem/B
 *    submission: https://codeforces.com/contest/1997/submission/380946387
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation, Trick
 *    complexity: O(n)
 *    metacognition: We have some fixed rules for the chosen cell because at first there is guaranteed that AT MOST 1 connected region
 *    note: Because there are at most 1 connected region at start so there is only 2 cases that we can block are - each case is just the flipped version of the other case:
 ...
 x.x
 and
 x.x
 ...
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
    if(!fopen("1997B.INP", "r")) return;
    freopen("1997B.INP", "r", stdin);
    freopen("1997B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    string a,b;
    cin >> a;
    cin >> b;

    int ans = 0;
    for(int i = 1; i < n-1; i++){
        if(a[i] == '.' && b[i] == '.' && b[i-1] == 'x' && b[i+1] == 'x' && a[i-1] == '.' && a[i+1] == '.') ans++;
        if(a[i] == '.' && b[i] == '.' && a[i-1] == 'x' && a[i+1] == 'x' && b[i-1] == '.' && b[i+1] == '.') ans++;
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