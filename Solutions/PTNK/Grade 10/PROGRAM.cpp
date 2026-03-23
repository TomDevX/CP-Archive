/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-30 14:41:55
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;
int n,m;
const int N = 1e5+1;
vector<int> adj[N], deg(N);
vector<long long> ans(N), t(N);
queue<int> qu;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    if(!fopen("PROGRAM.INP", "r")) return;
    freopen("PROGRAM.INP", "r", stdin);
    freopen("PROGRAM.OUT", "w", stdout);
}

void dfs(int u){
    for(int &v : adj[u]){
        ans[v] = max(ans[v],ans[u] + t[u]);
        deg[v]--;
        if(deg[v] <= 0) qu.push(v);
    }
}

int main(){
    fast();
    setup();
    
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> t[i];
    }

    int u,v;
    for(int i = 1; i <= m; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        deg[v]++;
    }

    for(int i = 1; i <= n; i++){
        if(deg[i] == 0){
            qu.push(i);
            ans[i] = 1;
        }
    }
    while(!qu.empty()){
        u = qu.front();
        dfs(u);
        qu.pop();
    }

    long long maxn = 0;
    for(int i = 1; i <= n; i++){
        maxn = max(maxn,ans[i] + t[i]);
    }
    cout << maxn-1 << '\n';
    for(int i = 1; i <= n; i++){
        cout << ans[i] << '\n';
    }
}