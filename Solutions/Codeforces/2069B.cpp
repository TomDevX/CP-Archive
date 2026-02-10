/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-10 11:25:37
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Set of Strangers
 *    source: https://codeforces.com/problemset/problem/2069/B
 *    submission: https://codeforces.com/problemset/submission/2069/362299991
 *    tags: greedy
 *    complexity: O(t\*n\*m)
 *    status: AC
 *    note: With greedy, we know that when we want to transform a value into another value, we only need to process 2 times maximum, because we only need to change those cells, and their side-sharing cells
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
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
const int X[4] = {0,0,1,-1};
const int Y[4] = {-1,1,0,0}; // check side-sharing cells
const int N = 2*490001;
int n,m;

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n >> m;
        vii a(n+1,vi(m+1));
        bitset<N> vis;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cin >> a[i][j];
            }
        }

        bool rekt = false; // this rekt variable will check if there's a cell that needs to perform 2 times to transform into another color
        
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                vis[a[i][j]] = 1;
                for(int k = 0; k < 4; k++){
                    int x = i + X[k];
                    int y = j + Y[k]; // indices of the adjacent cells
                    if(!check(x,y)) continue;
                    if(a[x][y] != a[i][j]) continue;
                    
                    vis[n*m + a[x][y]] = 1; // mark if they need 2 moves to transform into another color
                    rekt = true;
                }
            }
        }

        cout << vis.count()-1-rekt << '\n'; // if there's a "rekt" cells, we can make it as the target value to reduce 1 move
    }
}