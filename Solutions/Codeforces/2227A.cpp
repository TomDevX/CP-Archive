/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-30 21:35:46
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Koshary
 *    source: https://codeforces.com/contest/2227/problem/A
 *    submission: https://codeforces.com/contest/2227/submission/373070581
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Basic
 *    complexity: O(1)
 *    note: We will move the optimal way is that move by x first, then y. If both x and y are odd, we can't go to the destination because there is only 1 turn to move 1 stud
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
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
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
        int x,y;
        cin >> x >> y;
        cout << ((x&1) && (y&1) ? "NO" : "YES") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}