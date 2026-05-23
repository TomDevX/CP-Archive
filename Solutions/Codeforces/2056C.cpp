/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 08:55:18
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Palindromic Subsequences
 *    source: https://codeforces.com/contest/2056/problem/C
 *    submission: https://codeforces.com/contest/2056/submission/375701984
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Adhoc
 *    complexity: O(n) 
 *    note: To make the most palindrome possible, f(a) must be smallest, and the smallest we can make is 3 by just putting 1 -> n-2 and then "1 2" at last, we can make palindromes with 1 2 1, 1 3 1, 1 4 1,... 2 3 2, 2 4 2, 2 5 2,... -> which will make absolutely more than n, but in case of 6, it can't so just copy the example
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
    if(!fopen("2056C.INP", "r")) return;
    freopen("2056C.INP", "r", stdin);
    freopen("2056C.OUT", "w", stdout);
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
        int n;
        cin >> n;

        if(n == 6){
            cout << "1 1 2 3 1 2\n";
        }
        else{
            for(int i = 1; i <= n-2; i++) cout << i << ' ';
            cout << "1 2\n";
        }
    }
    
    return NAH_I_WOULD_WIN;
}