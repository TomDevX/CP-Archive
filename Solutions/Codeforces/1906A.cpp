/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-10 11:24:57
 *    country: Vietnam - VNM
 *    title: Easy as ABC
 *    source: https://codeforces.com/problemset/problem/1906/A
 *    submission: https://codeforces.com/problemset/submission/1906/362212391
 * ----------------------------------------------------------
 *    tags: Brute Force
 *    complexity: O(3^6)
 *    note: Just try all the cells
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#include <cmath>
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


// ----------------------- [ FUNCTIONS ] -----------------------
bool isCollapse(int x, int y, int a, int b){
    return x == a && y == b;
}

bool inRange(int x, int y, int a, int b){
    return abs(x-a) <= 1 && abs(y-b) <= 1;
}

bool check(int x, int y, int a, int b){
    return !isCollapse(x,y,a,b) && inRange(x,y,a,b);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    vector<vector<char>> a(4, vector<char>(4));
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            cin >> a[i][j];
        }
    }

    string ans = "CCC";

    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            for(int x = 1; x <= 3; x++){
                for(int y = 1; y <= 3; y++){
                    if(!check(i,j,x,y)) continue;
                    for(int u = 1; u <= 3; u++){
                        for(int v = 1; v <= 3; v++){
                            if(!check(x,y,u,v) || isCollapse(i,j,u,v)) continue;
                            string s;
                            s += a[i][j];
                            s += a[x][y];
                            s += a[u][v];

                            if(s < ans){
                                ans = s;
                                if(ans == "ABB"){
                                    dbg(make_pair(u,v), make_pair(x,y));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ans;
}