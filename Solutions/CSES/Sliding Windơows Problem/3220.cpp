/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-03 00:35:11
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Sliding Window Sum
 *    source: https://cses.fi/problemset/task/3220
 *    submission: https://cses.fi/problemset/result/17062878/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sliding Windows
 *    complexity: O(n)
 *    note: The problem statement might confuse you but it is a typical Sliding Window Sum problem
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
    if(!fopen("3220.INP", "r")) return;
    freopen("3220.INP", "r", stdin);
    freopen("3220.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;

    ll x,a,b,c;
    cin >> x >> a >> b >> c;

    ll ans = 0;
    int cur = x;
    int last = x;
    ll sum = x;
    for(int i = 2; i <= k; i++){
        cur = (a*cur + b)%c;
        sum += cur;
    }
    
    ans = sum;
    for(int i = k+1; i <= n; i++){
        sum -= last;
        last = (a*last + b)%c;
        cur = (a*cur + b)%c;
        sum += cur;
        ans ^= sum;
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}