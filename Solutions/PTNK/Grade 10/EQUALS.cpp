/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-02 08:52:46
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: DÃY TĂNG DẦN 
 *    source: EQUALS
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cassert>

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
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("EQUALS.INP", "r")) return;
    freopen("EQUALS.INP", "r", stdin);
    freopen("EQUALS.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5, INF = 2e9;

int a[N], pos[N], pre[N];
int dp[N];

// ----------------------- [ FUNCTIONS ] -----------------------
bool is_good(int x){
    return x != INF;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++){
        if(!pos[a[i]]) pos[a[i]] = i;
    }

    for(int i = 1; i <= n; i++) dp[i] = INF;
    dp[0] = 0;

    for(int i = 1; i <= n; i++){
        if(is_good(dp[i-1]) && a[i] >= a[i-1]){
            pre[i] = i-1;
            dp[i] = dp[i-1];
        }

        if(pos[a[i]] > 0){
            if(is_good(dp[pos[a[i]]-1]) && a[i] >= a[pos[a[i]]-1]){
                if(dp[pos[a[i]]-1] + 1 < dp[i]){
                    dp[i] = dp[pos[a[i]] - 1] + 1;
                    pre[i] = pos[a[i]] - 1;
                }
            }
        }
        
        // if(is_good(dp[pos[a[i]] - 1]) && a[i] >= a[pos[a[i]]-1] && dp[pos[a[i]] - 1] + 1 < dp[i]){
        //     dp[i] = dp[pos[a[i]] - 1] + 1;
        //     pre[i] = pos[a[i]] - 1;
        // }

        // changing pos
        if(is_good(dp[i-1]) && (dp[i-1] < dp[pos[a[i]] - 1] || pos[a[i]] == 0)){
            pos[a[i]] = i;
        }

        // pos[a[i]] = i;
    }

    for(int i = 1; i <= n; i++) cerr << dp[i] << ' ';
    cerr << '\n';

    assert(dp[n] <= INF);
    if(dp[n] == INF){
        cout << -1;
        return;
    }

    vpii trace;
    int cur = n;
    while(cur > 0){
        if(pre[cur] != cur-1) trace.eb(pre[cur] + 1, cur);
        cur = pre[cur];
    }


    cout << dp[n] << '\n';

    for(int i = sz(trace) - 1; i >= 0; i--){
        cout << trace[i].fi << ' ' << trace[i].se << '\n';
    }
}

int main(){
    fastio;
    setup();

    int tc = 1;
    // cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}