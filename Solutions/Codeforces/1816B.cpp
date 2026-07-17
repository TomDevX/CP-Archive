/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-02 20:16:03
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Grid Reconstruction
 *    source: https://codeforces.com/contest/1816/problem/B
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

        vvi a(3, vi(n+1));

        int r = 2*n, l = 1;
        for(int i = 1; i <= n; i++){
            if(i&1){
                a[1][i] = r--;
            }
            else a[2][i] = r--;
        }

        swap(a[2][2], a[2][n]);

        for(int i = 1; i <= n; i++){
            if(!(i&1)){
                a[1][i] = l++;
            }
            else a[2][i] = l++;
        }

        for(int i = 1; i <= 2; i++){
            for(int j = 1; j <= n; j++) cout << a[i][j] << ' ';
            cout << '\n';
        }
    }
}