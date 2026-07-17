/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-15 21:22:34
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tree Requests - Approach 2
 *    source: https://codeforces.com/problemset/problem/570/D
 *    submission: https://codeforces.com/problemset/submission/570/374623175
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Bitmask, Graph
 *    complexity: O(n + q)
 *    note: To know if the characters is palindrome, we need to ensure that the maximum number of characters which appears odd times is 1. So we can check odd/even with bit, so we use bitmask (changing bit by using operator XOR ^). Our plan is to store the current mask value of each depth, and then DFS. When we reach u in the query, let ans[id] = current_mask[depth]. Then continue traversing the children nodes of u, when returning back to u, we XOR current_mask[depth] with ans[id] (with the current value of past current_mask[depth]), so that the previous path on that depth is cancelled because x ^ x = 0, so we only keep the result of subtree u, and just check if  maximum number of characters which appears odd times is 1 to answer Yes/No.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

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
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

int val[N], h[N], mask[N], ans[N];
vpii queries[N];
vi adj[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    for(const pii& p : queries[u]){
        ans[p.se] = mask[p.fi];
    }
    mask[h[u]] ^= (1 << val[u]);
    
    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        dfs(v,u);
    }

    for(const pii& p : queries[u]){
        ans[p.se] ^= mask[p.fi];
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    for(int v = 2; v <= n; v++){
        int u;
        cin >> u;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    for(int i = 1; i <= n; i++){
        char c;
        cin >> c;
        val[i] = c - 'a';
    }

    for(int i = 1; i <= q; i++){
        int u,height;
        cin >> u >> height;
        height--;
        queries[u].eb(height,i);
    }

    dfs(1,1);

    for(int i = 1; i <= q; i++){
        cout << (__builtin_popcount(ans[i]) <= 1 ? "Yes" : "No") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}