/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-28 10:24:18
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Shifted MEX
 *    source: https://codeforces.com/problemset/problem/2185/C
 *    submission: https://codeforces.com/problemset/submission/2185/364781791
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation, Adhoc
 *    complexity: O(n \log n)
 *    note: The only thing that is not chaging is if the values in the array are sequential are not, so we count the longest sequential subarray length 
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

        for(int i = 1; i <= n; i++) cin >> a[i];
        sort(all(a,1));
        a.erase(unique(all(a,1)),a.end());
        n = sz(a)-1;

        int ans = 0, cur = 1;
        for(int i = 2; i <= n; i++){
            if(a[i] == a[i-1]+1){
                cur++;
            }
            else{
                ans = max(ans,cur);
                cur = 1;
            }
        }
        ans = max(ans,cur);
        // dbg(a,1);
        cout << ans << '\n';
    }
}