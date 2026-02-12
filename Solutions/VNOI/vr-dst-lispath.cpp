/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-08 20:53:51
 *    country: Vietnam - VNM
 *    title: Lis Path
 *    source: https://oj.vnoi.info/problem/vr_dst_lispath
 *    submission: https://oj.vnoi.info/submission/11673982
 * ----------------------------------------------------------
 *    tags: Dynamic Programming, Tree
 *    complexity: O(n \log n)
 *    note: We DFS on the tree normally and DP to get LIS normally, but we need to store the old value at that lis position on each vertex so we can do the recursive 
**/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
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
int n;
const int N = 2e5+2;
vi adj[N];
int a[N], lis[N];
int ans[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    int it = lower_bound(lis + 1, lis + n + 1, a[u]) - lis;
    ans[u] = max(it,ans[pre]);
    int old = lis[it];
    lis[it] = a[u];
    for(int v : adj[u]){
        if(v != pre) dfs(v,u);
    }
    lis[it] = old;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    memset(lis,0x3f,sizeof(lis));

    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
}