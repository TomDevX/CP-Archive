/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-05 09:53:43
 *    done in: <none>
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#if __has_include("debuggingz.h")
    #include "debuggingz.h"
    #define dbg(x,i) cerr << "BreakPoint(" << i << ") -> " << #x << " = " << (x) << '\n';
#else
    #define dbg(x,i)
#endif

#define all(x,bonus) (x).begin()+(bonus),(x).end()

using namespace std;
const int N = 1e5+1;
vector<int> adj1[N], adj0[N], par(N), h(N);

int n,m,k;

void fast(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

void setup(){
    if(!fopen("ROADS.INP", "r")) return;
    freopen("ROADS.INP", "r", stdin);
    freopen("ROADS.OUT", "w", stdout);
}

void init(){
    for(int i = 1; i <= n; i++){
        par[i] = i;
        h[i] = 0;
    }
}

int main(){
    fast();
    setup();
    
    cin >> n >> m >> k;
    int u,v;
    int id;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> id;
        if(id){
            adj1[u].push_back(v);
            adj1[v].push_back(u);
        }
        else{
            adj0[u].push_back(v);
            adj0[v].push_back(u);
        }
    }

    int min_k = 0;
    init();
    for(int i = 0; i < (int)adj.size(); )
}