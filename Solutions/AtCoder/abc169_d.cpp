/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-01 21:12:42
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Div Game
 *    source: https://atcoder.jp/contests/abc169/tasks/abc169_d
 *    submission: https://atcoder.jp/contests/abc169/submissions/76333546
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(\sqrt(n))
 *    note: Just make the most expo for the lowest prime factor as possible, like 2^1, 2^2, 2^3...
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
    if(!fopen("abc169_d.INP", "r")) return;
    freopen("abc169_d.INP", "r", stdin);
    freopen("abc169_d.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    ll n;
    cin >> n;

    int ans = 0;
    for(ll i = 2; i * i <= n; i++){
        if(n%i != 0) continue;

        int cnt = 0;
        while(n%i == 0){
            cnt++;
            n /= i;
        }

        int e = 1;
        while(cnt >= e){
            ans++;
            cnt -= e;
            e++;
        }
    }
    cout << ans + (n > 1);
    
    return NAH_I_WOULD_WIN;
}