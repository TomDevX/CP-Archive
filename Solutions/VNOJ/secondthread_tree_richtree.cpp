/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-17 10:36:49
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Filthy Rich Trees
 *    source: https://oj.vnoi.info/problem/secondthread_tree_richtree
 *    submission: https://oj.vnoi.info/submission/12326531
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour, Big Num, BIT
 *    complexity: O(n \log n)
 *    note: At first glance, this problem is probably euler tour, so first we do the DFS first. But this is the product, so our sum will go > 10^10. So to fix that, we need to accept the number error and use log2(pref[sum]). We also know that log2(b/a) = log2(b) - log2(a) and log2(a * b) = log2(a) + log2(b). So we can apply that to BIT, just same as original number but this time log2 so we just prefix sum on it. Because query() returns log2(bit1 * bit2 * bit3) so to get the rate between query_original(x) and query_original(y), we turn it into (2^{query(x)}/(2^{query(y)})) = 2^{query(x) - query(y)} (because query() returns log2 so the answer must have 2^)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <iomanip>
#include <cmath>

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
    if(!fopen("secondthread_tree_richtree.INP", "r")) return;
    freopen("secondthread_tree_richtree.INP", "r", stdin);
    freopen("secondthread_tree_richtree.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+5;

vi adj[N];
ld bit[N];
int tin[N], tout[N];
int a[N];
int timer = 0;
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tin[u] = ++timer;

    for(int v : adj[u]){
        if(v == pre) continue;

        dfs(v,u);
    }

    tout[u] = timer;
}

void update(int pos, ld val){
    for(; pos <= n; pos += pos&-pos){
        bit[pos] += val;
    }
}

ld get(int pos){
    ld res = 0;

    if(pos <= 0) return 0;

    for(; pos; pos -= pos&-pos) res += bit[pos];

    return res;
}

ld query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    fill(sub(a,1,n),1);

    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int u,val;
            cin >> u >> val;
            update(tin[u],log2l(val) - log2l(a[u]));
            a[u] = val;
        }
        else{
            int x,y;
            cin >> x >> y;

            ld ans = query(tin[x],tout[x]) - query(tin[y], tout[y]);

            if(ans > log2l(1e9)){
                cout << 1000000000 << '\n';
            }
            else cout << fixed << setprecision(7) << pow(2.0L, ans) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}