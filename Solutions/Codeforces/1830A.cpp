/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-02 21:08:29
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Copil Copac Draws Trees
 *    source: https://codeforces.com/contest/1830/problem/A
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
#include <queue>
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
    queue<pii> qu;

    while(tc--){
        int n;
        cin >> n;

        vector<pii> adj[n+1];
        vi t(n+1, 1e9);
        vector<bool> vis(n+1);
        
        for(int i = 1; i < n; i++){
            int u,v;
            cin >> u >> v;
            adj[u].eb(v,i);
            adj[v].eb(u,i);
        }
        t[1] = 0; // time
        vis[1] = 1;

        int ans = 1;
        qu.push({1,1});

        while(!qu.empty()){
            pii u = qu.front();
            qu.pop();

            for(pii v : adj[u.fi]){
                if(vis[v.fi]) continue;
                if(v.se < t[u.fi]){
                    qu.push({v.fi,u.se+1});
                    ans = max(ans,u.se+1);
                }
                else{
                    qu.push({v.fi,u.se});
                }
                t[v.fi] = v.se;
                vis[v.fi] = 1;
            }
        }

        cout << ans << '\n';
    }
}