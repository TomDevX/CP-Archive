/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-30 13:26:55
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

struct box{
    int v,id;
};

const int N = 51, M = 1001;
vector<box> adj[N];
vector<int> trace;
bitset<M> vis;
bitset<N> check;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    if(!fopen("NECKLACE.INP", "r")) return;
    freopen("NECKLACE.INP", "r", stdin);
    freopen("NECKLACE.OUT", "w", stdout);
}

void rest(){
    for(int i = 1; i < N; i++) adj[i].clear();
    vis.reset();
    trace.clear();
    check.reset();
}

void dfs(int u){
    while(!adj[u].empty()){
        box e = adj[u].back();
        adj[u].pop_back();
        if(vis[e.id]) continue;
        vis[e.id] = 1;
        dfs(e.v);
    }
    trace.push_back(u);
}

int main(){
    fast();
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        rest();
        int m;
        int n = 0;
        cin >> m;
        int u,v;
        for(int i = 1; i <= m; i++){
            cin >> u >> v;
            adj[u].push_back({v,i});
            adj[v].push_back({u,i});
            check[u] = !check[u];
            check[v] = !check[v];
            n = max({n,u,v});
        }   

        if(check.count()){
            cout << "NO\n";
            continue;
        }

        dfs(n);
        
        if((int)trace.size() != m+1){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
            for(int i = 0; i < m; i++){
                cout << trace[i] << ' ' << trace[i+1] << '\n';
            }
        }
    }
}