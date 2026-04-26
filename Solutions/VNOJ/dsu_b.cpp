/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-26 19:43:42
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Giá trị tập
 *    source: https://oj.vnoi.info/problem/dsu_b
 *    submission: https://oj.vnoi.info/submission/12190979
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(\log n)
 *    note: Still a typical DSU
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>
#include <cstring>

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
    if(!fopen("dsu_b.INP", "r")) return;
    freopen("dsu_b.INP", "r", stdin);
    freopen("dsu_b.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+2;
int par[N], sz[N], minn[N], maxn[N], mem[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
    iota(minn + 1, minn + N, 1);
    iota(maxn + 1, maxn + N, 1);
    fill(mem+1,mem + N, 1);
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
    minn[a] = min(minn[a], minn[b]);
    maxn[a] = max(maxn[a], maxn[b]);
    mem[a] += mem[b];

    par[b] = a;

    return true;
}

void get(int u){
    u = find_set(u);
    cout << minn[u] << ' ' << maxn[u] << ' ' << mem[u] << '\n';
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,q;
    cin >> n >> q;

    string type;
    while(q--){
        cin >> type;
        if(type == "union"){
            int a,b;
            cin >> a >> b;
            union_set(a,b);
        }
        else{
            int x;
            cin >> x;
            get(x);
        }
    }
    
    return NAH_I_WOULD_WIN;
}