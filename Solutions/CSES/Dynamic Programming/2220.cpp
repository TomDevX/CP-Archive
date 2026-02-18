/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-18 14:57:49
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Counting Numbers
 *    source: https://cses.fi/problemset/task/2220
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
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
ll solve(ll n){
    ll dp[19][10][2][2];
    dp[1][0][0][0] = 1;

    for(int i = 1; i < 18; i++){
        for(int cur = 0; cur <= 9; cur++){
            for(int lead = 0; lead < 2; lead++){
                for(int reached = 0; reached < 2; reached++){
                        
                }
            }
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    ll a,b;
    cin >> a >> b;
    cout << solve(b) - solve(a-1);
}