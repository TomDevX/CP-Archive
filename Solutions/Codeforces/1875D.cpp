/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-25 10:06:09
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Jellyfish and Mex
 *    source: https://codeforces.com/contest/1875/problem/D
 *    submission: https://codeforces.com/contest/1875/submission/375989918
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n^2)
 *    note: We need to consider which is the current MEX and which number we should cut, so we use DP
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
    if(!fopen("1875D.INP", "r")) return;
    freopen("1875D.INP", "r", stdin);
    freopen("1875D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll INF = 2e18;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;

        vi cnt(n+1);
        for(int i = 1; i <= n; i++){
            int x;
            cin >> x;
            if(x < n) cnt[x]++;
        }

        int mex = 0;
        while(cnt[mex]) mex++;

        vll dp(n+1,INF);
        dp[mex] = 0;

        for(int cur_mex = mex; cur_mex; cur_mex--){
            for(int i = 0; i < cur_mex; i++){
                dp[i] = min(dp[i], dp[cur_mex] + cur_mex*(cnt[i]-1) + i); // +i because cur_mex turned to i
            }
        }

        cout << dp[0] << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}