/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-05 22:46:02
 *    country: Vietnam - VNM
 *    title: 
 *    source: 
 *    submission: 
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
int n,m;
bool a[302][302];
int dp[302][302];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> m;
    int q = n*m;
    int ans = 0;
    while(q--){
        int x,y;
        cin >> x >> y;
        a[x][y] = 1;

        bool changed = true;
        for(int i = x; i <= n && changed; i++){
            changed = false;
            for(int j = y; j <= m; j++){
                int v = (a[i][j] ? min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1 : 0);
        
                if (dp[i][j] != v) {
                    dp[i][j] = v;
                    ans = max(ans, dp[i][j]);
                    changed = true;
                }
            }
        }
        cout << ans << '\n';
    }
}