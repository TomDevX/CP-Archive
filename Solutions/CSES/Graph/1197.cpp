
/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-26 13:00:15
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Cycle Finding
 *    source: https://cses.fi/problemset/task/1197
 *    submission: https://cses.fi/problemset/result/16382838/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Graph, Bellman Ford
 *    complexity: O(n \cdot m)
 *    note: We use bellman ford instead of SPFA to make the code more stabled on testcases
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
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
int n,m;
const int N = 2502;

struct node{
    int u;
    ll w;

    node(int _u = 0, ll _w = 0) : u(_u), w(_w) {};
};
vector<node> adj[N];
int ed;
int trace[N];
ll dis[N];

// ----------------------- [ FUNCTIONS ] -----------------------
bool SPFA(int src){
    dis[src] = 0;
    trace[src] = 0;

    for(int i = 1; i <= n; i++){
        for(int u = 1; u <= n; u++){
            for(node v : adj[u]){
                if(dis[v.u] > dis[u] + v.w){
                    dis[v.u] = dis[u] + v.w;
                    trace[v.u] = u;
                    if(i == n){ // found negative cycle
                        ed = v.u;
                        for(int k = 1; k <= n; k++) ed = trace[ed]; // to get back to one of the element on the negative cycle because ed is not guaranteed inside that cycle
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(dis,0x3f,sizeof(dis));

    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;

        adj[u].eb(v,w);
    }

    if(SPFA(1)){
        cout << "YES\n";

        vi res = {ed};
        int cur = trace[ed];

        
        while(cur != ed){
            res.eb(cur);
            cur = trace[cur];
        }

        for(int i = sz(res)-1 ;i >= 0; i--) cout << res[i] << ' ';
        cout << res.back();
    }
    else{
        cout << "NO";
    }
}