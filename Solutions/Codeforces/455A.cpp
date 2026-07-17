/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-13 15:49:12
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Boredom
 *    source: https://codeforces.com/contest/455/problem/A
 *    submission: https://codeforces.com/contest/455/submission/366471336
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(N)
 *    note: Let dp[i] = best answer you can get only with value 1 -> i. If we don't choose value i, we get the best previous value: dp[i-1]. If we choose value i, we get dp[i-2] + cnt[i]*i. Why only dp[i-2]? Because first it will skip the value i-1 for us, second when we go to value i+1, it will skip value i for us (because removing a[i]+1, a[i]-1 is symmetric) => fun fact that this solution will not change even if the problem states we only remove a[i]-1 or only remove a[i]+1
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("debuggingz.h")
#include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#ifdef LOCAL
    #include <iomanip>
    #include <ctime>
    #include <sys/resource.h>
    struct Statistic_Tracker {
        ~Statistic_Tracker() {
            struct rusage usage;
            getrusage(RUSAGE_SELF, &usage);
            double time = 1.0 * clock() / CLOCKS_PER_SEC;
            
            double mem = usage.ru_maxrss;
            #ifdef __APPLE__
                mem /= (1024.0 * 1024.0);
            #else
                mem /= 1024.0;
            #endif
    
            cerr << "\033[1;32m\n--------------------------------\033[0m\n";
            cerr << "\033[1;32mNAH I'D WIN!\033[0m | ";
            cerr << "\033[1;33mTime: " << fixed << setprecision(3) << time << "s\033[0m | ";
            cerr << "\033[1;36mMem: " << fixed << setprecision(2) << mem << "MB\033[0m\n";
        }
    } __TomDev_will_AK_VOI;
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
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
const int N = 1e5;
int cnt[N+2];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1, x; i <= n; i++){
        cin >> x;
        cnt[x]++;
    }

    vll dp(N+1);
    dp[0] = 0;
    dp[1] = cnt[1];

    for(int i = 2; i <= N; i++){
        dp[i] = max(dp[i-1], dp[i-2] + 1LL*cnt[i]*i);
    }

    cout << dp[N];
    
    return NAH_I_WOULD_WIN;
}