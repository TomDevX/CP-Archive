/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-02 11:15:56
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Just a Nim game? 
 *    source: https://marisaoj.com/problem/623
 *    submission: https://marisaoj.com/submission/1270916
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Game Theory, Misere Nim
 *    complexity: O(n)
 *    metacognition: Notice that the can't move player will win. So that our optimized case is to force the values on the piles all to <= 1 (because when the enemy moves, they must remove at least 1). So that all the piles are now has value <= 0, we don't care piles with 0. If there are even number of piles, we are the one will be unable to move first so we win and vice versa. So our optimized way is just move like normal Nim to turn it into all piles <= 1. Because moving like Nim helps you control the number left number
 *    note: Misere Nim
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
    if(!fopen("623.INP", "r")) return;
    freopen("623.INP", "r", stdin);
    freopen("623.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    ll x;
    ll ans = 0, cnt_1 = 0;
    for(int i = 1; i <= n; i++){
        cin >> x;
        ans ^= x;
        cnt_1 += (x == 1);
    }

    if(cnt_1 == n){
        cout << (cnt_1 & 1 ? "DA" : "ZE") << '\n';
    }
    else cout << (!ans ? "DA" : "ZE") << '\n';
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