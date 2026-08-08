/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-08-08 15:39:36
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Evanescent
 *    source: https://codeforces.com/contest/2254/problem/B
 *    submission: https://codeforces.com/contest/2254/submission/386216660
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation, Greedy
 *    complexity: O(n)
 *    metacognition: 
 *    note: Just check all possibilities
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
    if(!fopen("2254B.INP", "r")) return;
    freopen("2254B.INP", "r", stdin);
    freopen("2254B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    string s;
    cin >> s;

    int best_remove = 0;
    for(int i = 1; i < n-1; i++){
        if(s[i-1] != s[i] && s[i] != s[i+1]){
            best_remove = max(best_remove,1);
            if(s[i-1] == s[i+1]){
                best_remove = max(best_remove,2);
            }  
        }
    }

    int ans = 0;
    for(int i = 1; i < n; i++){
        if(s[i] != s[i-1]) ans++;
    }
    ans++;

    cout << ans - best_remove << '\n';
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}