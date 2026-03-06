/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-06 21:45:31
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: https://codeforces.com/contest/2121/problem/C
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
        int n,m;
        cin >> n >> m;
        vvi a(n+1,vi(m+1));
        
        int max_val = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cin >> a[i][j];
                max_val = max(max_val,a[i][j]);
            }
        }

        vector<pii> pos;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(a[i][j] == max_val) pos.eb(i,j);
            }
        }

        int val = -1;
        bool ok = true;
        for(int i = 1; i < sz(pos); i++){
            if(pos[i].fi != pos[0].fi){
                if(val == -1) val = pos[i].se;
                else if(val != pos[i].se){
                    ok = false;
                    break;
                }
            }
        }

        if(ok){
            cout << max_val-1 << '\n';
            continue;
        }

        val = -1;
        ok = true;
        for(int i = 1; i < sz(pos); i++){
            if(pos[i].se != pos[0].se){
                if(val == -1) val = pos[i].fi;
                else if(val != pos[i].fi){
                    ok = false;
                    break;
                }
            }
        }

        cout << (ok ? max_val-1 : max_val) << '\n';
    }
}