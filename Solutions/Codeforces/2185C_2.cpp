/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-28 10:58:40
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Shifted MEX
 *    source: https://codeforces.com/problemset/problem/2185/C
 *    submission: https://codeforces.com/problemset/submission/2185/364782560
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation, Adhoc
 *    complexity: O(n^2)
 *    note: We try all elements as x because we need a 0 for MEX not to be 0
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

    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vi a(n+1);

        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        sort(all(a,1));

        int ans = 0;
        for(int i = 1; i <= n; i++){
            int missing = 0;
            for(int j = 1; j <= n; j++){
                if(a[j] - a[i] == missing) missing++;
            }
            ans = max(ans,missing);
        }
        cout << ans << '\n';
    }
}