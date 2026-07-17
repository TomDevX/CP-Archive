/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-21 14:20:40
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Koala and Notebook
 *    source: https://codeforces.com/contest/1209/problem/F
 *    submission: https://codeforces.com/contest/1209/submission/379680947
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BFS, Graph
 *    complexity: O(n + m \log_{10} m)
 *    metacognition: Thought of Dijkstra (trace the shortest path) + Trie (to define the smaller value) or storing using string) -> But this seems too complicated in time complexity because need to use heap (it need to store and compare too many strings)
 *    note: Notice that each edge u -> v will have a weight of its index in the edges. So that, we can do normally do shortest path on this graph. But weight! The weight will be add up by digits, not total, so it will be integer overflow, and we can't even use modulo to compare (as the statement stated). So we have another way, now we can chop down the weights using virtual nodes (like from u -> v we have edge = 123 => u -1-> virt_1 -2-> virt_2 -3-> v) => when traversing the graph, we need to prefer the smallest digit as possible, and then reaching the vertex, fix its distance as dis[v] = (dis[u] * 10 + d)%MOD (with MOD = 1e9+7). So the best way for us to traverse the graph using this method is Lexicographical BFS. So we need to consider the total digits of the current distance AND the current digit => We need to combine a bit of Dial algorithm in this BFS (using buckets to store digits). Since we need to consider both current distance digits + current digit. We use vector to group nodes with the same number of digits into the queue, and to find the next most optimized step, we check from digit 0 -> 9 and continue grouping the new ones.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
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
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("1209F.INP", "r")) return;
    freopen("1209F.INP", "r", stdin);
    freopen("1209F.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const ll MOD = 1e9+7;
const int N = 1300005;

int n,m;
ll dis[N];
int virt;
int st[N];
int top_st = -1;
vi adj[N][10];
vi qu[N];
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void add(int u, int v, int w){
    while(w){
        st[++top_st] = w%10;
        w /= 10;
    }

    int cur = u;
    while(top_st > 0){
        adj[cur][st[top_st--]].eb(++virt);
        cur = virt;
    }

    adj[cur][st[top_st--]].eb(v);
}

void bfs(int src){
    int top = 0, tot = 0;
    qu[0] = {1};
    vis[1] = 1;

    while(top <= tot){
        vi cur = qu[top++];

        vi nxt[10];

        for(int d = 0; d <= 9; d++){
            for(int u : cur){
                for(int v : adj[u][d]){
                    if(vis[v]) continue;

                    vis[v] = 1;

                    dis[v] = (dis[u] * 10 + d)%MOD;

                    nxt[d].eb(v);
                }
            }
        }

        for(int d = 0; d <= 9; d++){
            if(!nxt[d].empty()) qu[++tot] = nxt[d];
        }
    }

}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> m;
    virt = n;

    for(int w = 1; w <= m; w++){
        int u,v;
        cin >> u >> v;
        add(u,v,w);
        add(v,u,w);
    }

    bfs(1);

    for(int u = 2; u <= n; u++){
        cout << dis[u] << '\n';
    }
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}