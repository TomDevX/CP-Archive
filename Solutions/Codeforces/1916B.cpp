/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-28 23:21:07
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Two Divisors
 *    source: https://codeforces.com/problemset/problem/1916/B
 *    submission: https://codeforces.com/problemset/submission/1916/364864584
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Number Theory
 *    complexity: O(1)
 *    note: We call p = smallest prime factor of x => b = x/p (because b is x largest divisor), so in order for a to be the second largest, 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
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

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
ll gcd(ll a, ll b){
    while(b != 0){
        ll temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}

ll lcm(ll a, ll b){
    return a*b/gcd(a,b);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int tc;
    cin >> tc;

    while(tc--){
        ll a,b;
        cin >> a >> b;

        cout << (b%a == 0 ? b*(b/a) : lcm(a,b)) << '\n';
    }
}