/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-01 09:33:32
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

        vvi a(n+1);
        for(int i = 1; i <= n; i++){
            int m;
            cin >> m;
            int x;
            for(int j = 1; j <= m; j++){
                cin >> x;
                a[i].eb(x);
            }
            reverse(all(a[i],0));
        }

        
        sort(all(a,1), [](const vi &x, const vi &y){
            for(int i = 0; i < min(sz(x),sz(y)); i++){
                if(x[i] < y[i]) return false;
                else if(x[i] > y[i]) return true;
            }
            return sz(x) <= sz(y);
        });

        vector<bool> vis(1e6+2);
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < sz(a[i]); j++){
                if(vis[a[i][j]]) continue;
                res.eb(a[i][j]);
                vis[a[i][j]] = 1;
            }
        }

        for(int i = sz(res)-1; i >= 0; i--) cout << res[i] << ' ';
        cout << '\n';
    }
}