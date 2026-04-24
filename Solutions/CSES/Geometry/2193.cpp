/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-24 22:02:03
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Polygon Lattice Points
 *    source: https://cses.fi/problemset/task/2193/
 *    submission: https://cses.fi/problemset/result/16998036/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Geometry
 *    complexity: O(n)
 *    note: Use Pick's theorem. To get B in the formula, we use gcd between the distance of x and y
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cmath>

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
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
    if(!fopen("2193.INP", "r")) return;
    freopen("2193.INP", "r", stdin);
    freopen("2193.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


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
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    vpll a(n+1);
    for(int i = 0; i < n; i++) cin >> a[i].fi >> a[i].se;
    a[n] = a[0];

    ll B = 0;
    ll S = 0;
    for(int i = 0; i < n; i++){
        B += gcd(abs(a[i+1].fi - a[i].fi), abs(a[i+1].se - a[i].se));
        S += a[i+1].fi*a[i].se - a[i].fi*a[i+1].se;
    }
    S = abs(S);

    ll I = S - B + 2;

    cout << (I >> 1) << ' ' << B;
    
    return NAH_I_WOULD_WIN;
}