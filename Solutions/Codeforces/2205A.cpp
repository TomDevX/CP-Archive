/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-01 09:07:50
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
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
        int n;
        cin >> n;
        vi a(n+1);

        int pos = 0;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] == n) pos = i;
        }

        int cnt = 0;
        int cur = 0;
        for(int i = 1; i <= n; i++){
            cur = max(cur,a[i]);
            if(a[i] == cur) cnt++;
        }

        swap(a[pos], a[1]);

        int cnt2 = 0;
        for(int i = 1; i <= n; i++){
            cur = max(cur,a[i]);
            if(a[i] == cur) cnt2++;
        }

        // if(cnt < cnt2) swap(a[pos],a[1]);
        for(int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << '\n';
    }
}