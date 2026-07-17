/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-04 15:17:02
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Product 1 Modulo N
 *    source: https://codeforces.com/problemset/problem/1514/C
 *    submission: https://codeforces.com/problemset/submission/1514/377256308
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n)
 *    note: We have 2 main observations: 1. Only if gcd(x,n) == 1 can contribute to the product because if it shares the same factor, there will always be that factor in the final product | 2. Because if gcd(a,n) == 1 && gcd(b,n) == 1 => gcd(a*b,n) = 1. So if the final product modulo N (P) != 1 => P < N && gcd(P,N) = 1 => we are already choose every number which has gcd(x,N) = 1 so P must be one of them, so just remove it and we'll get the remainder of 1
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("1514C.INP", "r")) return;
    freopen("1514C.INP", "r", stdin);
    freopen("1514C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

bitset<N> chose;

// ----------------------- [ FUNCTIONS ] -----------------------
int gcd(int a, int b){
    while(b){
        int tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    chose[1] = 1;
    ll cur = 1;
    for(int i = 2; i < n; i++){
        if(gcd(i,n) == 1){
            chose[i] = 1;
            cur = (cur*i)%n;
        }
    }

    if(cur != 1) chose[cur] = 0;
    cout << chose.count() << '\n';
    for(int i = 1; i < n; i++) if(chose[i]) cout << i << ' ';
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