/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-02 20:10:27
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Serval and Mocha's Array
 *    source: https://codeforces.com/contest/1789/problem/A
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
int gcd(int a, int b){
    while(b){
        int tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}

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
        for(int i =1 ; i <= n; i++) cin >> a[i];
        
        int minn= 1e9;
        for(int i = 1; i <= n; i++){
            for(int j = i + 1; j <= n; j++){
                minn = min(minn,gcd(a[i], a[j]));
            }
        }

        cout << (minn <= 2 ? "Yes" : "No") << '\n';
    }
}   