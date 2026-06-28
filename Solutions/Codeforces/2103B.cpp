/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-27 23:23:44
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Binary Typewriter
 *    source: https://codeforces.com/contest/2103/problem/B
 *    submission: https://codeforces.com/contest/2103/submission/380368850
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n)
 *    metacognition: Oh this is easy, just count it normally >< wait we can reverse a substring? => Mistake in reading statement -> Just need to consider the 2 digit at the start and end of substring because the switches in that substring would be the same even reversed, we can maximum reduce to switches => Now count the switches, if 
 *    note: 
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
    if(!fopen("2103B.INP", "r")) return;
    freopen("2103B.INP", "r", stdin);
    freopen("2103B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = '0' + s;

    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(s[i] != s[i-1]) ans++;
    }

    if(ans >= 3){
        cout << ans-2+n << '\n';
    }
    else if(ans == 2){
        cout << ans-1 + n << '\n';
    }
    else cout << ans + n << '\n';
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