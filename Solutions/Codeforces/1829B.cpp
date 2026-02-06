/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-06 16:07:12
 *    country: Vietnam - VNM
 *    title: Blank Space
 *    source: https://codeforces.com/problemset/problem/1829/B
 *    submission: https://codeforces.com/problemset/submission/1829/361679553
 * ----------------------------------------------------------
 *    tags: implementation
 *    complexity: O(t*n)
 *    note: Just do what the problem tell you to do
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

        int cnt = 0, ans = 0;
        int x;
        for(int i = 1; i <= n; i++){
            cin >> x;
            if(x == 0) cnt++;
            else{
                ans = max(ans,cnt);
                cnt = 0;
            }
        }
        cout << max(ans,cnt) << '\n';
    }
}