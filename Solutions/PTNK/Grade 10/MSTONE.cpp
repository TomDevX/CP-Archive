/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-30 08:58:14
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

const int N = 1e5+1;
vector<box> adj[N];
bitset<N> vis;
vector<int> trace;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    if(!fopen("MSTONE.INP", "r")) return;
    freopen("MSTONE.INP", "r", stdin);
    freopen("MSTONE.OUT", "w", stdout);
}

void dfs(int u){
    while(!adj[u].empty()){
        box e = adj[u].back();
        adj[u].pop_back();
        dfs(e.v);
        trace.push_back(e.id);
    }
}

int main(){
    fast();
    setup();

    int m,n;
    cin >> n >> m;
    int u,v;
    for(int i = 1; i <= m; i++){
        cin >> u >> v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }

    dfs(1);
    for(int i = 0; i < (int)trace.size(); i++) cout << trace[i] << ' ';
}

