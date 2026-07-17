/**
 * author: TomDev - Tran Hoang Quan
 * created: 2026-01-20 14:33:39
 * country: Vietnam - VNM
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <bitset>
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
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vll = vector<long long>;

void setup(){
    if(!fopen("SALARY.INP", "r")) return;
    freopen("SALARY.INP", "r", stdin);
    freopen("SALARY.OUT", "w", stdout);
}

const int N = 3e5+2;
int up[N][20], val[N], tin[N], tout[N], depth[N];
vi adj[N];
int m = 0;
const int M = 2*N + 10;
int bit[M], raw[M];

void dfs(int u){
    tin[u] = ++m;
    for(int i = 1; i <= 19; i++){
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for(int v : adj[u]){
        depth[v] = depth[u] + 1;
        dfs(v);
    }
    tout[u] = ++m;
}

void update_point(int pos, int v){
    raw[pos] = v;
    for(; pos <= m; pos += pos & -pos)
        bit[pos] = max(bit[pos], v);
}

int get(int l, int r){
    int res = 0;
    while(r >= l){
        if(r - (r & -r) + 1 >= l){
            res = max(res, bit[r]);
            r -= r & -r;
        } else {
            res = max(res, raw[r]);
            r--;
        }
    }
    return res;
}

int main(){
    fastio;
    setup();

    int n;
    cin >> n;
    up[0][0] = 0;
    cin >> val[0];

    for(int i = 1; i <= n; i++){
        cin >> val[i] >> up[i][0];
        adj[up[i][0]].eb(i);
    }

    dfs(0);
    update_point(tin[0], val[0]);
    update_point(tout[0], val[0]);
    
    for(int i = 1; i <= n; i++){
        int u = i;
        for(int k = 19; k >= 0; k--){
            int temp = get(tin[up[u][k]], tout[up[u][k]]);
            if(temp < val[i]){
                u = up[u][k];
            }
        }
        cout << depth[up[i][0]] - depth[u] + 1 << '\n';
        update_point(tin[i], val[i]);
        update_point(tout[i], val[i]);
    }
}