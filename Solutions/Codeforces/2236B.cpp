/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-09 21:33:58
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tatar TV Show
 *    source: https://codeforces.com/contest/2236/problem/B
 *    submission: https://codeforces.com/contest/2236/submission/381868185
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementaiton
 *    complexity: O(n)
 *    metacognition: Prioritize the current index to change it to 0 because we can only change the right one
 *    note: Prioritize to change the current index and check
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
    if(!fopen("2236B.INP", "r")) return;
    freopen("2236B.INP", "r", stdin);
    freopen("2236B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

int n,k;
string s;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> k;
    cin >> s;

    for(int i = 0; i < n-k; i++){
        if(s[i] == '1'){
            s[i] = '0';
            if(s[i + k] == '0') s[i + k] = '1';
            else s[i+k] = '0';
        }
    }

    bool is_good = true;
    for(int i = n-k; i < n; i++){
        if(s[i] == '1'){
            is_good = false;
            break;
        }
    }

    cout << (is_good ? "YES" : "NO") << '\n';
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