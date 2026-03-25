/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-25 10:14:55
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Updating Edges on Trees
 *    source: https://www.codechef.com/problems/UPDTREE
 *    submission: https://www.codechef.com/viewsolution/1252458834
 *    status: AC
 * ----------------------------------------------------------
 *    tags: LCA, Different array on tree
 *    complexity: O(n \log n)
 *    note: We find the intersect area of [a;b] and [c;d] by using lca at the start and end and then remove that one from diff array, then we do a diff array on the tree, then prefix sum. Notice that the problem update the value on edges, not verticals. The hard thing is getting the intersect, we know that with [a;b], a is the starting/ending point, same as b, and same approach with [c;d], and we know that if a and b are in different subtree, our path need to go up to parents and then down, so we need to find the 2 deepest intersect of [a;b] and [c;d] among the candidate {lca(a,c), lca(a,d), lca(b,c), lca(b,d)} - we are getting the smaller left and right boundary. About the difference array on tree, we do bottom-up, that means the child will update value to its parents and the root will get all of that values. But when building prefix sum, we do top-down for easier access
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
    if(!fopen("UPDTREE.INP", "r")) return;
    freopen("UPDTREE.INP", "r", stdin);
    freopen("UPDTREE.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int lg[N], up[N][19], diff[N], h[N];
ll pref[N];
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    for(int i = 2; i < N; i++) lg[i] = lg[i>>1] + 1;
}

void dfs(int u){
    for(int v : adj[u]){
        if(v == up[u][0]) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;

        for(int k = 1; k <= 18; k++) up[v][k] = up[up[v][k-1]][k-1];

        dfs(v);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u,v);

        int dis = h[u] - h[v];

        for(int k = 18; k >= 0; k--){
            if(dis >> k & 1) u = up[u][k];
        }
    }
    if(u == v) return u;

    for(int k = 18; k >= 0; k--){
        if(up[u][k] != up[v][k]) u = up[u][k], v = up[v][k];
    }
    return up[u][0];
}

int dist(int a, int b){
    return h[a] + h[b] - 2*h[lca(a,b)];
}

bool isOn(int a, int b, int x){
    return dist(a,b) == dist(a,x) + dist(x,b);
}

bool isOnBothPath(int a, int b, int c, int d, int x){
    return isOn(a,b,x) && isOn(c,d,x);
}

void remove_diff(int a, int b){
    diff[a]--;
    diff[b]--;
    diff[lca(a,b)] += 2;
}

void add_diff(int a, int b){
    diff[a]++;
    diff[b]++;
    diff[lca(a,b)] -= 2;
}

void dfs_diff(int u){
    for(int v : adj[u]){
        if(v == up[u][0]) continue;
        
        dfs_diff(v);
        
        diff[u] += diff[v];
    }
}

void build_pref(int u){
    for(int v : adj[u]){
        if(v == up[u][0]) continue;
        
        pref[v] = pref[u] + diff[v];
        
        build_pref(v);
    }
}

ll get_pref(int a, int b){
    return pref[a] + pref[b] - 2*pref[lca(a,b)];
}

bool cmp(int a, int b){
    return h[a] > h[b];
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,q,p;
    cin >> n >> q >> p;

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1);

    while(q--){
        int a,b,c,d;
        cin >> a >> b >> c >> d;

        vi can = {lca(a,c), lca(a,d), lca(b,c), lca(b,d)};
        vi good;
        for(int x : can){
            if(isOnBothPath(a,b,c,d,x)){
                good.eb(x);
            }
        }
        sort(all(good,0), cmp);
        filter(good,0);

        if(sz(good) > 1){
            remove_diff(good[0],good[1]);
        }

        add_diff(a,b);
    }

    dfs_diff(1);
    build_pref(1);

    while(p--){
        int u,v;
        cin >> u >> v;
        cout << get_pref(u,v) << '\n';
    }

    return NAH_I_WOULD_WIN;
}