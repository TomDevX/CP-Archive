/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-11 23:20:39
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Minimal Grid Path
 *    source: https://cses.fi/problemset/task/3359
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
#include <queue>
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
int n;
const int N = 3002;
char a[N][N];
const int X[2] = {0,1};
const int Y[2] = {1,0};

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
        }
    }
    cout << a[1][1];

    queue<pii> qu;
    qu.push({1,1});
    int level = 1;
    while(!qu.empty()){
        int x = qu.front().fi, y = qu.front().se;
        qu.pop();

        char minn = 'Z' + 1;
        for(int k = 0; k < 2; k++){
            int newx = x + X[k];
            int newy = y + Y[k];
            if(!check(newx,newy)) continue;

            minn = min(minn,a[newx][newy]);
        }
        
        int cur_level = x+y;
        if(cur_level > level){
            level = cur_level;
            cout << minn;
        }

        for(int k = 0; k < 2; k++){
            int newx = x + X[k];
            int newy = y + Y[k];
            if(!check(newx,newy) || a[newx][newy] != minn) continue;

            qu.push({newx,newy});
        }
    }
    cout << a[n][n];
}