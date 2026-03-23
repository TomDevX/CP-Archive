/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-21 09:07:58
 *    country: Vietnam - VNM
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
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;

void setup(){
    if(!fopen("promote.in", "r")) return;
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    pii a[4];
    for(int i = 0; i < 4; i++){
        cin >> a[i].fi >> a[i].se;
    }

    int rem = 0;
    vi res;
    for(int i = 3; i >= 0; i--){
        if(rem > a[i].fi){
            rem -= a[i].fi;
            a[i].fi = 0;
        }
        else{
            a[i].fi -= rem;
            rem = 0;
        }
        res.eb(a[i].se - a[i].fi);
        rem += a[i].se - a[i].fi;
    }

    for(int i = sz(res)-1; i >= 1; i--) cout << res[i] << '\n';
}