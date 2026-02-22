/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-22 21:27:53
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Cucumber
 *    source: https://account.marisaoj.com/problem/556
 *    submission: https://account.marisaoj.com/submission/1094391
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n \log n)
 *    note: We use priority queue and a bit greedy
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <functional>
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

    int n;
    cin >> n;
    vector<pii> a(n+1);
    int tot = 0;

    for(int i = 1; i <= n; i++){
        cin >> a[i].fi;
    }
    for(int i = 1; i <= n; i++){
        cin >> a[i].se;
        tot += a[i].se;
    }

    sort(all(a,1));

    priority_queue<int,vi,greater<int>> pq;

    int d = 1;
    for(int i = 1; i <= n; i++){
        if(a[i].fi >= d){
            d++;
            pq.push(a[i].se);
        }
        else if(pq.top() < a[i].se){
            pq.pop();
            pq.push(a[i].se);
        }
    }

    while(!pq.empty()){
        tot -= pq.top();
        pq.pop();
    }

    cout << tot;
}