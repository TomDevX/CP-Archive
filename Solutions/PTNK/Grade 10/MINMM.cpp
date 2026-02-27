/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-26 13:34:59
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: MINMM
 *    source: BT_20260226.pdf
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
#include <deque>
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
using ld = long double;
using pll = pair<long long,long long>;
using pld = pair<long double,long double>;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

void setup(){
    if(!fopen("MINMM.INP", "r")) return;
    freopen("MINMM.INP", "r", stdin);
    freopen("MINMM.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n, k;
    cin >> n >> k;

    k = n-k;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    sort(all(a,1));

    vi dis(n);
    for(int i = 1; i < n; i++){
        dis[i] = a[i+1] - a[i];
    }

    deque<int> dq;
    dq.push_back(1);
    for(int i = 2; i < k; i++){
        while(!dq.empty() && dis[dq.back()] > dis[i]){
            dq.pop_back();
        }
        dq.push_back(i);
    };

    int ans = 1e9;
    for(int i = k; i <= n; i++){
        if(dq.front() < i-k+1) dq.pop_front();
        ans = min(ans, a[i] - a[i-k+1] + dis[dq.front()]);
        if(i < n){
            while(!dq.empty() && dis[dq.back()] > dis[i]){
                dq.pop_back();
            }
            dq.push_back(i);
        }
    }   
    cout << ans;
}