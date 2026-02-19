/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-18 14:57:49
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Counting Numbers
 *    source: https://cses.fi/problemset/task/2220
 *    submission: https://cses.fi/problemset/result/16314439/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Digit
 *    complexity: O(digit(n) \cdot 9 \cdot 2 \cdot 2 \cdot 9)
 *    note: We úe classic DP Digit for this problem
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
    if(n < 0) return 0;

    ll dp[22][10][2][2] = {};
    dp[1][0][0][1] = 1; // starts with the prev number is 0
    string s = to_string(n);
    s = '#' + s;

    for(int i = 1; i < sz(s); i++){
        for(int prev = 0; prev <= 9; prev++){
            for(int lead = 0; lead < 2; lead++){
                for(int tight = 0; tight < 2; tight++){
                    if(dp[i][prev][lead][tight] == 0) continue;

                    int lim = tight ? s[i] - '0' : 9; // if tight is reached, lim must be lower than 9
                    for(int d = 0; d <= lim; d++){
                        if(lead && d == prev) continue; // not legal

                        int new_tight = tight && (d == lim); // if d is reached, we change the tight status
                        int new_lead = lead || d != 0; // if we no longer lead with '0' digit, we change the lead status

                        dp[i+1][d][new_lead][new_tight] += dp[i][prev][lead][tight];
                    }
                }
            }
        }
    }

    ll ans = 0;

    for(int d = 0; d <= 9; d++){
        for(int lead = 0; lead < 2; lead++){
            for(int tight = 0; tight < 2; tight++){
                ans += dp[sz(s)][d][lead][tight];
            }
        }
    }
    return ans;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    ll a,b;
    cin >> a >> b;
    cout << solve(b) - solve(a-1); //ensure answer is in range [a,b]
}