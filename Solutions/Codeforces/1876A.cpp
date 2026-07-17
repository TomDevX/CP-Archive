/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-06 21:22:17
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Helmets in Night Light
 *    source: https://codeforces.com/contest/1876/problem/A
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
        int n,p;
        cin >> n >> p;

        vector<pii> a(n+1);
        for(int i = 1; i <= n; i++) cin >> a[i].fi;
        for(int i = 1; i <= n; i++) cin >> a[i].se;

        sort(all(a,1), [](const pii& x, const pii& y){
            if(x.se == y.se) return x.fi > y.fi;
            return x.se < y.se;
        });

        ll ans = p;
        int cur = 1;
        int nxt = 2;

        while(nxt <= n && a[cur].se < p){
            ans += 1LL*a[cur].se*(min(a[cur].fi, n - nxt + 1));
            nxt += a[cur].fi;
            cur++;
        }

        nxt = min(n+1,nxt);
        ans += 1LL*p*(n-nxt+1);

        cout << ans << '\n';
    }
}