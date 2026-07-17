/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-20 15:37:11
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Two Substrings
 *    source: https://codeforces.com/problemset/problem/550/A
 *    submission: https://codeforces.com/problemset/submission/550/367457931
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    note: We just need to check if at a position there's a AB and BA and right behind or after it is not AB/BA
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>
#include <bitset>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
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
    if(!fopen("550A.INP", "r")) return;
    freopen("550A.INP", "r", stdin);
    freopen("550A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
bitset<N> hasAB, hasBA;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;
    int n = sz(s);
    s = '#' + s;

    int cntAB = 0, cntBA = 0;

    for(int i = 1; i < n; i++){
        if(s[i] == 'A' && s[i+1] == 'B'){
            cntAB++;
            hasAB[i] = 1;
        }
    }
    
    for(int i = 1; i < n; i++){
        if(s[i] == 'B' && s[i+1] == 'A'){
            cntBA++;
            hasBA[i] = 1;
        }
    }

    for(int i = 1; i < n; i++){
        if((hasAB[i] && cntBA - hasBA[i+1] - hasBA[i-1] > 0) || (hasBA[i] && cntAB - hasAB[i+1] - hasAB[i-1] > 0)){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    
    return NAH_I_WOULD_WIN;
}