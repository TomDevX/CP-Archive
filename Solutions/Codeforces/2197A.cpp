/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 16:33:11
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Friendly Numbers
 *    source: https://codeforces.com/contest/2197/problem/A
 *    submission: https://codeforces.com/contest/2197/submission/375741274
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Adhoc
 *    complexity: O(1)
 *    note: Just print all the testcases and you will see that the answer will be only 0 or 10. But it doesn't follow any rules, so just check from number n + 1 to n + 90 -> enough
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("2197A.INP", "r")) return;
    freopen("2197A.INP", "r", stdin);
    freopen("2197A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
int sdigit(int n){
    int cnt = 0;
    while(n){
        cnt += n%10;
        n /= 10;
    }
    return cnt;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;

        cout << ([&n]() noexcept -> int {
            for(int i = 1; i <= 90; i++){
                if(n + i - sdigit(n + i) == n) return 10;
            }
            return 0;
        })() << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}