/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-13 10:50:09
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: PHÂN CHIA MẢNG
 *    source: DT 13-07-2026.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log \log n)
 *    metacognition: Maybe if the number is prime, it must != group with number 1 >< but the array has many elements not just 1 to n -> For x/y = p, number of x's prime factor must = number of y's prime factor + 1 (that one is the prime number p), so it means that the team will be the parity of x's number of prime factor
 *    note: Separate the team by the parity of that element's number of prime factors in order to make it number of x's prime factor != number of y's prime factor + 1
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
    if(!fopen("matrix.INP", "r")) return;
    freopen("matrix.INP", "r", stdin);
    freopen("matrix.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;

int cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    // fill(all(cnt,2),1);
    for(int i = 2; i < N; i++){
        if(cnt[i] > 0) continue;
        for(int j = i; j < N; j += i) cnt[j] = i;
    }

    for(int i = 2; i < N; i++){
        int p = cnt[i];
        cnt[i] = cnt[i/p] + 1;
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    for(int i = 1, x; i <= n; i++){
        cin >> x;
        cout << (cnt[x] & 1 ? 1 : 2) << ' ';
    }
}

int main(){
    fastio;
    setup();
    sieve();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}