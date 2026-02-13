/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-13 08:07:12
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Projects
 *    source: https://cses.fi/problemset/task/1140
 *    submission: https://cses.fi/problemset/result/16252002/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: We use coordinate compress to compress the starting and ending times of event. Let dp[t] = maximum amount of money you can earn from time 1 -> i. So dp[t] will get the result from the previous projects which have the ending time < starting time of current event. At a project i, you can choose or not choose it base on if the previous result is more optimized than choosing project i
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
struct box{
    int a,b,p;

    box(int _a = 0, int _b = 0, int _p = 0) : a(_a), b(_b), p(_p) {};
    bool operator < (const box& other) const{
        return b < other.b;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;

    vector<box> a(n+1);
    vi sorted((n<<1)+1);

    for(int i = 1; i <= n; i++){
        cin >> a[i].a >> a[i].b >> a[i].p;
        sorted[(i<<1)-1] = a[i].a;
        sorted[i<<1] = a[i].b;
    }
    
    // sort the projects by ending time
    sort(all(a,1));

    // coordinate compression
    sort(all(sorted,1));
    for(int i = 1; i <= n; i++){
        a[i].a = lower_bound(all(sorted,1),a[i].a) - sorted.begin();
        a[i].b = lower_bound(all(sorted,1),a[i].b) - sorted.begin();
    }

    vll dp((n<<1)+1);
    int last = 0;
    ll best = 0;

    for(int i = 1; i <= n; i++){
        // write the best answer from previous results
        for(int j = last+1; j <= a[i].b; j++) dp[j] = best; // j also includes a[i].b so if dp[a[i].b] = best means that we dont choose project i
        last = a[i].b;

        dp[a[i].b] = max(dp[a[i].b], dp[a[i].a-1] + a[i].p); // check max the result from projects that are before the starting point of project i

        best = max(best,dp[a[i].b]);
    }

    cout << *max_element(all(dp,1)); // choose the best option
}