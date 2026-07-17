/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-27 11:13:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Trò con bò
 *    source: https://oj.vnoi.info/problem/dsu_c
 *    submission: https://oj.vnoi.info/submission/12194300
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(K \alpha(N))
 *    note: Typical DSU but we need to apply Inclusion-Exclusion for the sum
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>  

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
    if(!fopen("dsu_c.INP", "r")) return;
    freopen("dsu_c.INP", "r", stdin);
    freopen("dsu_c.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int par[N], sum[N], sz[N];
int n,q;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par+1,par+N,1);
}

int find_set(int u){
    if(u == par[u]) return u;
    int root = find_set(par[u]);
    if(par[u] != root){
        sum[u] += sum[par[u]]; // add the sum back (because we minus it before)
        par[u] = root;
    }
    return root;
}

bool union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a == b) return true;

    if(sz[a] < sz[b]) swap(a,b);
    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;
    sum[b] -= sum[a]; // minus so when we trace back we won't get effected to negative because -sum[a] + sum[a] = 0, and the plus in find_set above will add the extra during queries

    return false;
}

void add(int u, int val){
    u = find_set(u);
    sum[u] += val;
}

int get(int u){
    int bonus = (find_set(u) == u ? 0 : sum[find_set(u)]);
    return sum[u] + bonus;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    cin >> n >> q;
    while(q--){
        string type;
        cin >> type;
        if(type == "join"){
            int a,b;
            cin >> a >> b;
            union_set(a,b);
        }
        else if(type == "add"){
            int u,val;
            cin >> u >> val;
            add(u,val);
        }
        else{
            int x;
            cin >> x;
            cout << get(x) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}