/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-08 10:00:26
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Laura and Operations
 *    source: https://codeforces.com/contest/1900/problem/B
 *    submission: https://codeforces.com/contest/1900/submission/370219147`
 *    status: AC
 * ----------------------------------------------------------
 *    tags: math
 *    complexity: O(1)
 *    note: Now consider the case we are querying digit 1, and apply the same with digit 2 and 3. If the digit 2,3 are 0, we have already satisfied the problem. Else, we need digit 2,3 to have the same parity, because if they have a different parity, the max number in digit 2,3 can't be made to 0;
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
    if(!fopen("1900B.INP", "r")) return;
    freopen("1900B.INP", "r", stdin);
    freopen("1900B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int a, int b, int c){
    return ((b&1)^(c&1)) == 0;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int a,b,c;
        cin >> a >> b >> c;

        cout << (check(a,b,c) ? 1 : 0) << ' ' << (check(b,a,c) ? 1 : 0) << ' ' << (check(c,a,b) ? 1 : 0) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}