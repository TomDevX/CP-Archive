/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-15 10:56:39
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Elevator Rides
 *    source: https://cses.fi/problemset/task/1653
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
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
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n, s;
    cin >> n>> s;

    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(all(a,1));
    dbg(a,1);
    int ans = 0;

    while(sz(a) > 1){
        int sum = s;
        int cur = sz(a)-1;
        sum -= a[cur];
        a.erase(a.begin()+cur);

        int it = upper_bound(all(a,1), sum) - a.begin() - 1;
        // dbg(sum,it);
        while(it > 0 && sum - a[it] >= 0){
            sum -= a[it];
            a.erase(a.begin()+it);
            it = upper_bound(all(a,1), sum) - a.begin() - 1;
        }
        // dbg(a,1);
        ans++;  
    }
    cout << ans;
}