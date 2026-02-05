/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-05 23:10:35
 *    country: Vietnam - VNM
 *    title: Meet in the Middle
 *    source: https://cses.fi/problemset/task/1628/
 *    submission: https://cses.fi/paste/39bb411c336d08d8f6c8f1/
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Implementation, Optimization
 *    complexity: O(2^{\frac{n}{2}}*log({\frac{n}{2}}) + 2^{\frac{n}{2}}*log({\frac{n}{2}}))
 *    note: 
 *    1. We can divide our array into two halves, and then bitmask on the first half to find all the possible sums, we call every sum in this subset is A
 *    2. For the second half, we can do the same bitmask, call every sum in this second subset B, but now we find if the x-B is available in the first half? => x-B = A
 *    3. We can find out that if it is available by using map or unordered_map, but both of them are slow with a contant in the time complexity, so we can save them all into a vector with only 2^{\frac{n}{2}} elements, then we can count the occurences by using the upper_bound index - lower_bound index of x-B
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
using vlll = vector<vector<long long>>;

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

    int n,s;
    cin >> n >> s;

    int mid = n>>1;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vi tot;
    tot.reserve(1 << mid);

    for(int mask = 0; mask < (1 << mid); mask++){
        int sum = 0;
        for(int j = mask; j > 0; j &= (j-1)){
            sum += a[__builtin_ctz(j)+1];
            if(sum > s) break;
        }   
        if(sum <= s) tot.eb(sum);
    }

    ll ans = 0;
    sort(all(tot,0));
    for(int mask = 0; mask < (1 << (n-mid)); mask++){
        int sum = 0;
        for(int j = mask; j > 0; j &= (j-1)){
            sum += a[__builtin_ctz(j)+1+mid];
            if(sum > s) break;
        }
        if(sum <= s){
            int it = lower_bound(all(tot,0), s-sum) - tot.begin();
            if(tot[it] == s-sum) ans += upper_bound(all(tot,0),s-sum) - tot.begin() - it;
        }
    }
    cout << ans;
}