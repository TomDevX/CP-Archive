/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-19 11:16:55
 *    country: Vietnam - VNM
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
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;

void setup(){
    if(!fopen("TWOARR.INP", "r")) return;
    freopen("TWOARR.INP", "r", stdin);
    freopen("TWOARR.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------
struct node{
    int x,y;

    node(int _x = 0, int _y = 0) : x(_x), y(_y) {};
};

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    // int cnt = 1;

    int tc;
    cin >> tc;
    while(tc--){
        int n,x,y;
        cin >> n >> x >> y;
        vector<node> a(n+1);

        for(int i = 1; i <= n; i++){
            cin >> a[i].x;
        }
        for(int i = 1; i <= n; i++){
            cin >> a[i].y;
        }

        int minx = 1e9, maxx = -1e9;
        node boxx = {(int)-1e9,(int)-1e9}, boxy = {(int)-1e9,(int)-1e9};
        for(int i = 1; i <= n; i++){
            minx = min(minx, a[i].x - a[i].y);
            maxx = max(maxx, a[i].x - a[i].y);
            if(boxx.x < a[i].x){
                boxx = a[i];
            }
            if(boxy.y < a[i].y){
                boxy = a[i];
            }
        }

        if(maxx - minx > x + y){
            cout << -1 << '\n';
            continue;
        }

        node boxC = {boxx.x, boxy.y + abs(boxy.x - boxx.x) + x};
        node boxA = {boxx.x, boxy.y + abs(boxy.x - boxx.x)};
        // dbg(boxA.y,cnt++);
        node boxB = {boxA.x - x, boxA.y - y};

        ll ans = 0;
        for(int i = 1; i <= n; i++){
            if(a[i].y >= boxB.y && a[i].x >= boxB.x) continue;
            ll cost = 0;
            if(a[i].y < boxB.y) cost = boxB.y - a[i].y;
            if(a[i].x < boxB.x) cost = max(cost, 1LL*(boxB.x - a[i].x));
            ans += cost;
        }
        cout << ans << '\n';
    }
}