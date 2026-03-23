/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-01-30 12:20:11
 *    country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <queue>
#include <cstring>
#include <algorithm>
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
using vii = vector<vector<int>>;
using vll = vector<long long>;
using vlll = vector<vector<long long>>;

void setup(){
    if(!fopen("NAME.INP", "r")) return;
    freopen("NAME.INP", "r", stdin);
    freopen("NAME.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m,c,r,k;
const int N = 5e4+2;
struct node{
    int u,w,id;

    node(int _u, int _w, int _id = 0) : u(_u), w(_w), id(_id) {};
    bool operator<(const node& other) const{
        return w > other.w;     
    }
};
vector<node> adj[N];
priority_queue<node> pq;
pii dis[N][10];
int lim = 2e9;

// ----------------------- [ FUNCTIONS ] -----------------------
bool get(int x){
    for(int i = 0; i < k; i++){
        if(dis[x][i].se == 0) return false;
    }
    return true;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n >> m >> c >> r >> k;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 10; j++){
            dis[i][j].fi = lim;
        }
    }

    for(int i = 1; i <= m; i++){
        int u,v,l;
        cin >> u >> v >> l;
        
        adj[u].eb(v,l);
        adj[v].eb(u,l); 
    }

    for(int i = 1; i <= c; i++){
        pq.push({i,0,i});
        dis[i][0] = {0,i};
    }

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();

        int maxu = 0;
        for(int i = 0; i < k; i++) maxu = max(maxu, dis[u.u][i].fi);
        if(u.w > maxu) continue;

        for(node v : adj[u.u]){
            int maxv = 0, pos = 0;
            for(int i = 0; i < k; i++){
                if(dis[v.u][i].se == u.id){
                    maxv = dis[v.u][i].fi;
                    pos = i;
                    break;
                }
                if(dis[v.u][i].fi > maxv){
                    maxv = dis[v.u][i].fi;
                    pos = i;
                }
            }

            if(u.w + v.w <= r && maxv > u.w + v.w){
                dis[v.u][pos] = {u.w + v.w,u.id};
                pq.push({v.u,dis[v.u][pos].fi,u.id});
            }
        }
    }

    vi res;
    for(int i = c+1; i <= n; i++){
        if(get(i)){
            res.eb(i);
        }
    }
    cout << sz(res) << '\n';
    for(int i = 0; i < sz(res); i++) cout << res[i] << '\n';
}