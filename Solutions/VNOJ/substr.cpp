/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-17 21:49:47
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Xâu con
 *    source: https://oj.vnoi.info/problem/substr
 *    submission: https://oj.vnoi.info/submission/12330557
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n + m)
 *    note: Basic hashing
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("substr.INP", "r")) return;
    freopen("substr.INP", "r", stdin);
    freopen("substr.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;

const ll MOD = 1234567891;
ll hashA[N], POW[N];
ll base = 31;
ll hashB = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
ll getA(int l, int r){
    return ((hashA[r] - hashA[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string a,b;
    cin >> a >> b;
    int n = sz(a), m = sz(b);
    a = "#" + a;
    b = "#" + b;

    POW[0] = 1;
    for(int i = 1; i <= n; i++){
        POW[i] = (POW[i-1]*base)%MOD;
    }

    for(int i = 1; i <= n; i++){
        hashA[i] = (hashA[i-1]*base + a[i] - 'a' + 1)%MOD;
    }
    for(int i = 1; i <= m; i++){
        hashB = (hashB*base + b[i] - 'a' + 1)%MOD;
    }

    for(int i = 1; i + m - 1 <= n; i++){
        if(getA(i,i + m - 1) == hashB){
            cout << i << ' ';
        }
    }
    
    return NAH_I_WOULD_WIN;
}