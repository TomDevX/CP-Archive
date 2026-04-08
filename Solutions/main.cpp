/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-07 20:04:59
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <stack>
#include <cstring>
#include <queue>
#include <bitset>

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
#define range(x,st,ed) (x).begin()+(st),(x).begin()+(ed)+1
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m,q;
const int N = 5e4+2;
vi adj[N], E[N];
int num[N], low[N], id[N], idE[N], deg_in[N], h[N], lg[N], up[N][20];
int scc = 0, cnt = 0, sccE = 0;
stack<int> st;
bitset<N> del;

// ----------------------- [ FUNCTIONS ] -----------------------
void tarjan(int u){
    num[u] = low[u] = ++cnt;
    st.push(u);
    for(int v : adj[u]){
        if(del[v]) continue;
        if(num[v]){
            low[u] = min(low[u], num[v]);
            continue;
        }

        tarjan(v);
        low[u] = min(low[u],low[v]);
    }

    if(num[u] == low[u]){
        int v;
        scc++;
        do{
            v = st.top();
            st.pop();
            id[v] = scc;
            del[v] = 1;
        }while(v != u);
    }
}

void dfsE(int u){
    num[u] = 1;
    for(int v : E[u]){
        h[v] = h[u]+1;
        up[v][0] = u;
        for(int k = 1; k <= 18; k++){
            up[v][k] = up[up[v][k-1]][k-1];
        }
        dfsE(v);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int diff = h[u] - h[v];
        for(int k = 18; k >= 0; k--){
            if(diff >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int k = 18; k >= 0; k--){
        if(up[u][k] != up[v][k]){
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

bool check(int a, int b){
    int mid = lca(a,b);
    return a == mid;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
    }

    for(int i = 1; i <= n; i++){
        if(num[i] == 0){
            tarjan(i);
        }
        lg[i] = lg[i>>1] + 1;
    }

    for(int u = 1; u <= n; u++){
        for(int v : adj[u]){
            if(id[u] != id[v]){
                E[id[u]].eb(id[v]);
                deg_in[id[v]]++;
            }
        }
    }

    queue<int> qu;
    memset(num,0,sizeof(num));
    for(int u = 1; u <= scc; u++){
        if(deg_in[u] == 0) qu.push(u);
    }

    while(!qu.empty()){
        int u = qu.front();
        qu.pop();

        if(num[u] == 0) dfsE(u);
        for(int v : adj[u]){
            if(deg_in[v] == 1){
                deg_in[v]--;
                qu.push(v);
            }
        }
    }


    while(q--){
        int u,v;
        cin >> u >> v;
        cout << (check(id[u],id[v]) ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}