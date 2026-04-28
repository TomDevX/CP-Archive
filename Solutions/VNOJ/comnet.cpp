/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-28 15:55:54
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: VOI 13 Bài 3 - Mạng truyền thông
 *    source: https://oj.vnoi.info/problem/comnet
 *    submission: https://oj.vnoi.info/src/12204687
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU, MST
 *    complexity: O(q \cdot m + m \log m + q \cdot s \log s)
 *    note: On each query, sort the original edges first. Then make a separate array for changed edges, sort them on each Q query. Do Kruskal algo on the edges (remember to prefer the changed edges if met on the original one) with two pointers on 2 arrays. We only union_set with all edges that has w < target_w (in case there are multiple MST) and then check
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>
#include <numeric>
#include <bitset>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h") && defined(LOCAL)
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
    if(!fopen("comnet.INP", "r")) return;
    freopen("comnet.INP", "r", stdin);
    freopen("comnet.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2, M = 1e6+2;

int new_w[M], cur_w[M], par[N], sz[N];
bitset<M> ischanged;
int editedEdge[M], edges[M];
int hisid = 0;

// struct Edge{
//     int u,v;
    
//     Edge(int _u = 0, int _v = 0) : u(_u), v(_v) {};
// };

// struct DSU_change{
//     int u,v;
//     bool sz_changed;

//     DSU_change(int _u = 0, int _v = 0, bool _sz_changed = false) : u(_u), v(_v), sz_changed(_sz_changed) {};
// };

pii adj[M];
// DSU_change his[M];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    iota(par + 1, par + n + 1, 1);
    memset(sz,0,sizeof(sz[0])*(n+1));
}

// void rollback(int ver){
//     while(hisid > ver){
//         DSU_change last = his[hisid];
//         hisid--;

//         par[last.v] = last.v;
//         if(last.sz_changed) sz[last.u]--;
//     }
// }

void restQ(int n, int s){
    init(n);
    // rollback(0);
    for(int i = 1; i <= s; i++){
        ischanged[editedEdge[i]] = 0;
    }
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);

    // his[++hisid] = DSU_change(a,b,(sz[a]==sz[b]));

    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;
}


void solve(int n, int m, int q){
    for(int i = 1; i <= m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        cur_w[i] = w;
        adj[i] = {u,v};
        edges[i] = i;
    }
    sort(edges + 1, edges + m + 1, [](const int id1, const int id2) noexcept -> bool {
        return cur_w[id1] < cur_w[id2];
    });
    
    while(q--){
        int k,s;
        cin >> k >> s;
        int target_w = cur_w[k];
        
        for(int i = 1; i <= s; i++){
            int id, w;
            cin >> id >> w;
            new_w[id] = w;
            editedEdge[i] = id;
            ischanged[id] = 1;
        }
        if(ischanged[k]) target_w = new_w[k];
        
        sort(editedEdge + 1, editedEdge + s + 1, [](const int id1, const int id2) noexcept -> bool {
            return new_w[id1] < new_w[id2];
        });
        
        int l1 = 1, l2 = 1;
        while(l1 <= m || l2 <= s){
            int cur;
            while(l1 <= m && ischanged[edges[l1]]) l1++;
            if(l1 <= m && (l2 > s || cur_w[edges[l1]] < new_w[editedEdge[l2]])){
                cur = edges[l1++];
            }
            else{
                cur = editedEdge[l2++];
            }
            
            if((ischanged[cur] ? new_w[cur] : cur_w[cur]) >= target_w) break;
            union_set(adj[cur].fi, adj[cur].se);
        }
        
        cout << (find_set(adj[k].fi) ==  find_set(adj[k].se) ? "YES" : "NO") << '\n';

        restQ(n,s);
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    
    init(1e5);
    while(tc--){
        int n,m,q;
        cin >> n >> m >> q;

        solve(n,m,q);
        // restTC(n);
    }
    
    return NAH_I_WOULD_WIN;
}
