/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-01 22:23:20
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Kim tự tháp
 *    source: https://oj.vnoi.info/problem/gogovoi_kimtuthap
 *    submission: https://oj.vnoi.info/submission/12617368
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("gogovoi_kimtuthap.INP", "r")) return;
    freopen("gogovoi_kimtuthap.INP", "r", stdin);
    freopen("gogovoi_kimtuthap.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 4e5+5;

int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int norm(int x){
    x %= 3;
    if(x < 0) x += 3;
    return x;
}

int Cnk(int n, int k){
    if(n < k) return 0;
    if(n == k || k == 0) return 1;
    return 2; 
}

int lucas(int n, int k){
    int res = 1;
    while(n || k){
        res = (res * Cnk(n%3, k%3))%3;
        n /= 3;
        k /= 3;
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    char c;
    for(int i = 1; i <= n; i++){
        cin >> c;
        if(c == 'B') a[i] = 0;
        else if(c == 'W') a[i] = 1;
        else a[i] = 2;
    }

    // (-1)^{n-1} * sum(1 -> n){(n-1)C(i-1)*a_{i}} mod 3
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans = (ans + lucas(n-1,i-1)*a[i])%3;
    }

    if((n-1)&1) ans = norm(-ans);

    if(ans == 0) cout << 'B';
    else if(ans == 1) cout << 'W';
    else cout << 'R';
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