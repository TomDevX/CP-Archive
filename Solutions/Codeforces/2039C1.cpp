/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-04 09:03:56
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Shohag Loves XOR (Easy Version)
 *    source: https://codeforces.com/contest/2039/problem/C1
 *    submission: https://codeforces.com/gym/676327/submission/365315587
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Bit
 *    complexity: O(x)
 *    note: For x XOR y to be divisor candidate of x, x XOR y must be <= 2*x. And if y > 2*x, x XOR y can't be the divisor because x XOR y has the same ost significant bit with y
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <algorithm>
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


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int tc;
    cin >> tc;
    while(tc--){
        int x;
        ll m;
        cin >> x >> m;

        int cnt = 0;
        for(int i = 1; i <= min(2LL*x,m); i++){
            if(x != i && (x%(x^i) == 0 || i%(x^i) == 0)){
                cnt++;
            }
        }

        cout << cnt << '\n';
    }
}