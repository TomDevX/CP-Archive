/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-24 22:52:51
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Shifts and Sorting
 *    source: https://codeforces.com/contest/1969/problem/B
 *    submission: https://codeforces.com/contest/1969/submission/364214311
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy, Implementation
 *    complexity: O(tc*n)
 *    note: We need to move all 0s before the first 1. After moving 1 0s, we remove it from the future swaps by the counter
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string>
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


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int tc;
    cin >> tc;
    while(tc--){
        string s;
        cin >> s;
        int n = sz(s);
        s = '#' + s;

        bool met1 = false;
        int one = n;
        ll ans = 0;
        ll counter = 0;

        for(int i = 1; i <= n; i++){
            if(s[i] == '1'){
                met1 = true;
                one = min(one,i);
            }
            else if(met1){
                ans += (i-one+1)-counter;
                counter++;
            }
        }
        cout << ans << '\n';
    }
}