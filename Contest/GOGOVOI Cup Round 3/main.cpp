/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-06 08:07:32
 *    country: Vietnam - VNM
 *    title: 
 *    source: 
 *    submission: 
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
 **/

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <cstring>
#include <algorithm>
#include <queue>
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
int a[N], ans[N], val[N];
vi adj[N];
int st[4*N];
priority_queue<int> child[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, int v){
    if(l == r){
        if(v == 0 && !child[l].empty()) child[l].pop();
        else child[l].push(v);
        return;
    }

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    if(pos <= mid) update(left,l,mid,pos,v);
    else update(left|1,mid+1,r,pos,v);

    int x = (l == mid ? child[l].top() : st[left]);
    int y = (r == mid+1 ? child[r].top() : st[left|1]);
    st[id] = max(x,y);
}

int get(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id];

    int mid = l + ((r-l)>>1);
    int left = id<<1;

    return max(get(left,l,mid,u,v),get(left|1,mid+1,r,u,v));
}

void dfs(int u){
    update(1,1,n,val[u],ans[u]);
    for(int v : adj[u]){
        dfs(v);
        ans[u] = max(ans[u], get(1,1,n,1,val[u])+1);
    }
    update(1,1,n,val[u],0);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        val[i] = a[i];
        ans[i] = 1;
    }
    sort(a+1,a+n+1);
    for(int i = 1; i <= n; i++){
        val[i] = lower_bound(a + 1, a + n + 1, val[i]) - a;
    }

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
    }

    dfs(1);
    for(int i = 1; i<= n; i++){
        cout << ans[i] << '\n';
    }
}