/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-23 09:20:23
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bến tàu
 *    source: KT_20260323.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
    if(!fopen("PIER.INP", "r")) return;
    freopen("PIER.INP", "r", stdin);
    freopen("PIER.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
ll n,a,b;

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(ll mid){
    return 1.0L*mid/b >= 1.0L*(n-mid)/a;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> a >> b;

    ll l = 2, r = n-1;
    ll ans = 0;
    while(l <= r){
        int mid = l + ((r-l)>>1);
        if(check(mid)){ // s/a >= s/b
            r = mid-1;
            ans = mid;
        }
        else l = mid+1;
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}