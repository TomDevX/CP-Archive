/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-01 11:15:46
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
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

struct box{
    int u,v;
    long long w;
};

const int N = 1e5+1;
vector<box> edges(N);
vector<int> par(N,-1);
int n,m;

int find_set(int u){
    if(par[u] < 0) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int u, int v){
    u = find_set(u);
    v = find_set(v);
    if(par[u] > par[v]) swap(u,v);

    if(par[u] == par[v]) par[u]--;
    par[v] = u;
}

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("KRUSKAL.INP", "r", stdin);
    freopen("KRUSKAL.OUT", "w", stdout);
}

long long kruskal(){
    long long res = 0;
    int cnt = 0;
    sort(edges.begin()+1,edges.begin()+m+1,[](const box& a, const box& b){
        return a.w < b.w;
    });

    for(int i = 1; i <= m; i++){
        int u = find_set(edges[i].u), v = find_set(edges[i].v); long long w = edges[i].w;
        
        if(u == v) continue;
        res += w;
        union_set(u,v);
        cnt++;
        if(cnt == n-1) break;
    }

    return (cnt == n-1 ? res : -1);
}

int main(){
    fast();
    setup();
    
    cin >> n >> m;
    int u,v;
    long long w;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        edges[i] = {u,v,w};
    }

    cout << kruskal();
}