/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-10 09:31:20
 *    country: Vietnam - VNM
 *    title: Collecting Numbers
 *    source: https://cses.fi/problemset/task/2216
 *    submission: https://cses.fi/problemset/result/16218047/
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n)
 *    note: We mark the indices of all elements, and then check if the greater has a smaller index
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

using namespace std;

#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    int x;
    for(int i = 1; i <= n; i++){
        cin >> x;
        cnt[x] = i;
    }

    int ans = 1;
    for(int i = 2; i <= n; i++){
        if(cnt[i] < cnt[i-1]) ans++;
    }
    cout << ans;
}