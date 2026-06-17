/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-17 09:13:17
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>
#include <stack>

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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int M = 4e5+5, N = 2e5+5;

struct Edge{
    int u,v,s;

    Edge(int _u = 0, int _v = 0, int _s = 0) : u(_u), v(_v), s(_s) {};
};

Edge E[M];
vi adj[N];

bitset<N> del;
bitset<M> bad;
int low[N], num[N], group[N];
int cnt = 0, scc = 0;
int st[N];
int top = 0;
int n,m;

// ----------------------- [ FUNCTIONS ] -----------------------
void rest(int n, int m){
    for(int i = 1; i <= n; i++){
        adj[i].clear();
        low[i] = num[i] = del[i] = 0;
        group[i] = 0;
    }
    for(int i = 1; i <= m; i++) bad[i] = 0;
    top = scc = 0;
}

void tarjan(int u){
    num[u] = low[u] = ++cnt;
    st[++top] = u;

    for(int v : adj[u]){
        if(del[v] || v == n) continue;
        if(num[v] == 0) tarjan(v),low[u] = min(low[u], low[v]);
        else low[u] = min(low[u],num[v]);
    }
    if(low[u] == num[u]){
        int v = 0;
        scc++;
        do{
            v = st[top--];
            del[v] = 1;
            group[v] = scc;
        }while(v != u);
    }
}


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> m;
    rest(n,m);
    
    for(int i = 1; i <= m; i++){
        cin >> E[i].u >> E[i].v >> E[i].s;
        adj[E[i].u].eb(E[i].v);
    }

    for(int i = 1; i < n; i++){
        if(!num[i]) tarjan(i);
    }

    for(int i = 1; i <= m; i++){
        if(E[i].s == -1) bad[i] = 1;
    }

    for(int i = 1; i <= m; i++){
        if(E[i].s > -1 && !bad[E[i].s] && group[E[i].u] == group[E[i].v]){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}