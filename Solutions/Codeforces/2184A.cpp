/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-24 14:04:32
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cmath>
#include <algorithm>
#include <iomanip>
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
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("TDN.INP", "r")) return;
    freopen("TDN.INP", "r", stdin);
    freopen("TDN.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const long double pi = acos(-1);

// ----------------------- [ FUNCTIONS ] -----------------------
long double get_dis(pair<ll,ll> &a, pair<ll,ll> &b){
    return 1.0L*((a.fi-b.fi)*(a.fi-b.fi) + (a.se-b.se)*(a.se-b.se))/8.0L;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    vector<pair<ll,ll>> a(n+1);
    for(int i = 0; i < n; i++){
        cin >> a[i].fi >> a[i].se;
    }
    a[n] = a[0];

    long double ans = 0;
    for(int i = 0; i < n; i++){
        ans += get_dis(a[i], a[i+1])*pi;
    }

    cout << fixed << setprecision(6) << ans/pi;
}
