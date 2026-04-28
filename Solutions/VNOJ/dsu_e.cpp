/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-27 14:33:22
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Cutting a graph
 *    source: https://oj.vnoi.info/problem/dsu_e
 *    submission: https://oj.vnoi.info/submission/12194751
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(q \alpha(n))
 *    note: Just reverse the queries and answer it offline
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
    if(!fopen("dsu_e.INP", "r")) return;
    freopen("dsu_e.INP", "r", stdin);
    freopen("dsu_e.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
struct Query{
    bool type;
    int a,b;

    Query(bool _type = false, int _a = 0, int _b = 0, int _id = 0) : type(_type), a(_a), b(_b){};
};
const int N = 5e4+2;
int par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

bool union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return true;

    if(sz[a] < sz[b]) swap(a,b);
    if(sz[a] == sz[b]) sz[a]++;
    par[b] = a;

    return false;
}

bool check(int a, int b){
    return find_set(a) == find_set(b);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,m,q;
    cin >> n >> m >> q;

    for(int i = 1, tmp; i <= m; i++){
        cin >> tmp >> tmp;
    }

    vector<Query> queries(q+1);
    for(int i = 1; i <= q; i++){
        string type;
        int a,b;
        cin >> type >> a >> b;
        queries[i] = Query((type == "cut"),a,b,i);
    }

    reverse(all(queries,1));

    vector<bool> ans;
    ans.reserve(q);
    for(int i = 1; i <= q; i++){
        Query &Q = queries[i];
        if(Q.type){
            union_set(Q.a, Q.b);
        }
        else{
            ans.eb(check(Q.a,Q.b));
        }
    }

    reverse(all(ans,0));
    for(bool b : ans){
        cout << (b ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}