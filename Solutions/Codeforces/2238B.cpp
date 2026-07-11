/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-09 21:34:17
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Crimson Triples
 *    source: https://codeforces.com/contest/2238/problem/B
 *    submission: https://codeforces.com/contest/2238/submission/381872884
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
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
    if(!fopen("2238B.INP", "r")) return;
    freopen("2238B.INP", "r", stdin);
    freopen("2238B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
ll gcd(ll a, ll b){
    while(b){
        ll tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

ll lcm(ll a, ll b){
    return a/gcd(a,b) * b;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    // ll ans = 0;
    // for(int a = 1; a <= n; a++){
    //     for(int b = 1; b <= n; b++){
    //         for(int c = 1; c <= n; c++){
    //             if(gcd(lcm(a,b), lcm(b,c)) == gcd(a,c)){
    //                 if(min({a,b,c}) != 1) cerr << a << ' ' << b << ' ' << c << '\n';
    //                 ans++;
    //             }
    //         }
    //     }
    // }

    ll real_ans = 1LL*n*n;
    for(int i = 2; i <= n; i++){
        ll m = n/i;
        real_ans += m*m;
    }

    // cout << ans << '\n';
    cout << real_ans << '\n';
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