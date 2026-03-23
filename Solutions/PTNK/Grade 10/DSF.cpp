/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2025-12-02 14:54:44
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
// #include <vector>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;

const int N = 1e5+1;
vector<int> par(N,-1);

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    freopen("DSF.INP", "r", stdin);
    freopen("DSF.OUT", "w", stdout);
}

int find_set(int u){
    if(par[u] < 0) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int u, int v){
    u = find_set(u), v = find_set(v);
    if(par[u] > par[v]){
        swap(u,v);
    }
    if(par[u] == par[v]) par[u]--;
    par[v] = u;
}

int main(){
    fast();
    // setup();
    
    int n,m;
    cin >> n >> m;
    int u,v;
    int cnt = n;
    for(int i  =1; i <= m; i++){
        cin >> u >> v;
        u = find_set(u), v = find_set(v);
        if(u != v){
            union_set(u,v);
            cnt--;
        }
        cout << cnt << '\n';
    }
}