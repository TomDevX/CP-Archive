/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-01 10:13:50
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <cstring>
#include <bitset>
#include <queue>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

struct box{
    int u;
    long long w;

    bool operator<(const box& other) const{
        return w > other.w;
    }
};

const int N = 1e5+1;
vector<box> adj[N];
// vector<int> pre(N);
vector<long long> dis(N,1e18);
int n,m;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("DIJKSTRA.INP", "r", stdin);
    freopen("DIJKSTRA.OUT", "w", stdout);
}

void diks(int s){
    priority_queue<box> pq;
    dis[s] = 0;
    pq.push({s,0});
    while(!pq.empty()){ 
        box temp = pq.top();
        int u = temp.u;
        long long w = temp.w;
        pq.pop();
        if(w > dis[u]) continue;
        for(const box &nx : adj[u]){
            int v = nx.u;
            w = nx.w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                // pre[v] = u;
                pq.push({v,dis[v]});
            }
        }
    }
}

int main(){
    fast();
    setup();
    
    int u,v;
    long long w;
    cin >> n >> m;

    for(int i = 1 ; i <= m; i++){
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        // adj[v].push_back({u,w});
    }

    diks(1);
    if(dis[n] == 1e18){
        cout << -1;
        return 0;
    }

    // int cur = n;
    // vector<int> res;
    // while(cur != 0){
    //     res.push_back(cur);
    //     cur = pre[cur];
    // }
    cout << dis[n];
    // for(int i = (int)res.size()-1; i >= 0; i--) cout << res[i] << ' ';
}