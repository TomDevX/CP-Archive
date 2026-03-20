/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-20 15:27:32
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Two Buttons
 *    source: https://codeforces.com/problemset/problem/520/B
 *    submission: https://codeforces.com/problemset/submission/520/367456276
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BFS/DFS
 *    complexity: O(n)
 *    note: We can use BFS on state and get the minimum moves with a queue of pair int
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <bitset>
#include <queue>

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
    if(!fopen("520B.INP", "r")) return;
    freopen("520B.INP", "r", stdin);
    freopen("520B.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m;
const int N = 2e4+2;
bitset<N> vis;
int ans = -1;

// ----------------------- [ FUNCTIONS ] -----------------------
void bfs(int src){
    vis[src] = 0;
    queue<pii> qu;
    qu.push({src,0});

    while(!qu.empty()){
        pii u = qu.front();
        qu.pop();

        int v = u.fi*2;
        if(v <= 2e4 && !vis[v]){
            if(v == m){
                ans = u.se+1;
                return;
            }
            vis[v] = 1;
            qu.push({v,u.se+1});
        }

        v = u.fi-1;
        if(v >= 0 && !vis[v]){
            if(v == m){
                ans = u.se+1;
                return;
            }
            vis[v] = 1;
            qu.push({v,u.se+1});
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> m;
    
    bfs(n);

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}