/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-17 22:57:13
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Building Teams
 *    source: https://cses.fi/problemset/task/1668
 *    submission: https://cses.fi/problemset/result/16295973/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph
 *    complexity: O(V + E) 
 *    note: Use BFS to take turns between team 1 and 2
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
#include <queue>
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
const int N = 1e5+2;
vi adj[N];
bitset<N> vis;
int ans[N];
bool ok = true;
queue<int> qu;

// ----------------------- [ FUNCTIONS ] -----------------------
void bfs(int src){
    ans[src] = vis[src] = 1;

    qu.push(src);

    while(!qu.empty()){
        int u = qu.front();
        qu.pop();

        for(int v : adj[u]){
            if(vis[v]){
                if(ans[v] == ans[u]){
                    ok = false;
                    return;
                }
                continue;
            }
            vis[v] = 1;
            ans[v] = (ans[u] == 1 ? 2 : 1);
            qu.push(v);
        }
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    for(int i = 1; i <= n; i++){
        if(!vis[i]) bfs(i);
    }

    if(!ok){
        cout << "IMPOSSIBLE"; 
    }
    else{
        for(int i = 1; i <= n; i++){
            cout << ans[i] << ' ';
        }
    }
}