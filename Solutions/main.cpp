/**
 *    author: TomDev - Tran Hoang Quan
<<<<<<< Updated upstream
 *    created: 2026-03-02 09:26:53
=======
 *    created: 2026-03-02 09:09:04
>>>>>>> Stashed changes
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
const ll MOD = 1e9+7;
int n,k;
const int N = 1e6+2;
int cnt[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

<<<<<<< Updated upstream
    
=======
    cin >> n >> k;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    vll dp(n+1), pref(n+1);
    dp[0] = pref[0] = 1;

    int last = 1;
    int avail = 0;

    for(int i = 1; i <= n; i++){
        cnt[a[i]]++;
        if(cnt[a[i]] == 1) avail++;

        while(last < i && cnt[a[last]] > 1){
            cnt[a[last]]--;
            last++;
        }

        if(avail == k){
            dp[i] = pref[last-1];
            // dbg(dp[i],i);
        }
        pref[i] = (pref[i-1] + dp[i])%MOD;
    }
    cout << dp[n];
>>>>>>> Stashed changes
}