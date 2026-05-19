/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-17 22:43:37
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Finding Borders - Approach 1
 *    source: https://cses.fi/problemset/task/1732
 *    submission: https://cses.fi/problemset/result/17204250/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Z-func
 *    complexity: O(n)
 *    note: Typical Z-func
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
    if(!fopen("1732.INP", "r")) return;
    freopen("1732.INP", "r", stdin);
    freopen("1732.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
vi zf(string &s){
    int n = sz(s);

    vi z(n);

    for(int i = 1, l = 0, r = 1; i < n; i++){
        if(i <= r){
            z[i] = min(r-i+1, z[i-l]);
        }

        while(i < n && s[z[i]] == s[i + z[i]]) z[i]++;

        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;
    int n = sz(s);

    vi z = zf(s);

    for(int i = n-1; i >= 0; i--){
        if(z[i] == n-i) cout << z[i] << ' ';
    }
    
    return NAH_I_WOULD_WIN;
}