/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-28 10:16:18
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Everybody Likes Good Arrays!
 *    source: https://codeforces.com/problemset/problem/1777/A
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
        vi a(n+1);

        for(int i = 1; i <= n; i++) cin >> a[i];
        int cnt = 0;

        for(int i = 2; i <= n; i++){
            if(a[i]&1 && a[i-1]&1){
                a[i] = 1;
                cnt++;
            }
            else if(!(a[i]&1) && !(a[i-1]&1)){
                a[i] = 2;
                cnt++;
            }
        }
        cout << cnt  << '\n';
    }
}