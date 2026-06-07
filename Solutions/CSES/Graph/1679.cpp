/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-06 01:34:49
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Course Schedule
 *    source: https://cses.fi/problemset/task/1679/
 *    submission: https://cses.fi/problemset/result/17444915/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Topo Sort
 *    complexity: O(n)
 *    note: Just topo sort
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <queue>
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
    if(!fopen("1679.INP", "r")) return;
    freopen("1679.INP", "r", stdin);
    freopen("1679.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

vi adj[N];
int deg_in[N];
bitset<N> vis, inqueue;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int u,v;
        cin >> u >> v;
        deg_in[v]++;
        adj[u].eb(v);
    }

    queue<int> qu;
    for(int i = 1; i <= n; i++){
        if(!deg_in[i]) qu.push(i), inqueue[i] = 1;
    }

    vi ans;

    while(!qu.empty()){
        int u = qu.front();
        qu.pop();

        ans.eb(u);

        inqueue[u] = 0;
        vis[u] = 1;

        for(int v : adj[u]){
            if(vis[v]){
                cout << "IMPOSSIBLE";
                return;
            }
            if(inqueue[v]) continue;

            if(--deg_in[v] == 0){
                qu.push(v);
                inqueue[v] = 1;
            }
        }
    }

    if(sz(ans) != n){
        cout << "IMPOSSIBLE";
        return;
    }

    for(int u : ans) cout << u << ' ';
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