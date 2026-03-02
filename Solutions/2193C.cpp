/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-28 11:13:28
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Replace and Sum
 *    source: https://codeforces.com/problemset/problem/2193/C
 *    submission: https://codeforces.com/problemset/submission/2193/364783372
 *    status: AC
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
        int n,q;
        cin >> n >> q;

        vi a(n+1), b(n+1);

        int x;
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++){
            cin >> x;
            a[i] = max(a[i],x);
        }

        for(int i = n-1; i >= 1; i--){
            a[i] = max(a[i], a[i+1]);
        }

        vll pref(n+1);
        for(int i = 1; i <= n; i++) pref[i] = a[i] + pref[i-1];

        while(q--){
            int l,r;
            cin >> l >> r;
            cout << pref[r] - pref[l-1] << ' ';
        }
        cout << '\n';
    }
}