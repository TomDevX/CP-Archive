/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-04 09:04:09
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Dual (Easy Version)    
 *    source: https://codeforces.com/contest/1854/problem/A1
 *    submission: https://codeforces.com/contest/1854/submission/367846325
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n \log n)
 *    note: We add the max element to the whole array to make it the same sign, now if the sign is negative, we do a suffix to guarantee it is non-decrease, else we do the prefix with the same purpose
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
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

        int pos = 1;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(i > 1 && abs(a[pos]) < abs(a[i])) pos = i;
        }

        vector<pii> trace;
        for(int i = 1; i <= n; i++){
            if(a[i] * a[pos] < 0){
                trace.eb(i,pos);
            }
        }

        if(a[pos] < 0){
            for(int i = n-1; i >= 1; i--){
                trace.eb(i,i+1);
            }
        }
        else{
            for(int i = 2; i <= n; i++){
                trace.eb(i,i-1);
            }
        }

        cout << sz(trace) << '\n';
        for(pii &p : trace){
            cout << p.fi << ' ' << p.second << '\n';
        }
    }
}