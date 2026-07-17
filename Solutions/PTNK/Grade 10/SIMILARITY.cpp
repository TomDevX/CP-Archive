/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-06 02:48:23
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Độ tương đồng
 *    source: BT_20260406.pdf
 *    submission: 
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Z-function
 *    complexity: O(n + m)
 *    note: Typical Z-function
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
    #include "TomDev.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n'
#else
    #define dbg(x,i)
#endif
#define NAH_I_WOULD_WIN 0

// --- [ MACROS ] ---
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
#define filter(x,bonus) (x).erase(unique((x).begin()+(bonus), (x).end()), (x).end())
#define rall(x,bonus) (x).rbegin(),(x).rend()-(bonus)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fi first
#define se second
#define eb emplace_back
#define sz(x) (int)(x).size()

// --- [ TYPES & ALIASES ] ---
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("SIMILARITY.INP", "r")) return;
    freopen("SIMILARITY.INP", "r", stdin);
    freopen("SIMILARITY.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
vi zf(string &s){
    int n = sz(s);
    vi z(n);
    for(int i = 1, l = 0,r = 0; i < n; i++){
        if(i <= r){
            z[i] = min(r-i+1, z[i-l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;
    
    vi z = zf(s);

    ll ans = 0;
    for(int i = 0; i < sz(s); i++) ans += z[i];
    // dbg(z,1);
    cout << ans + sz(s);
    
    return NAH_I_WOULD_WIN;
}
