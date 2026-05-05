/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-05 14:31:46
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: KẾT BẠN
 *    source: https://ptnkoj.com/problem/tin_ketban
 *    submission: https://ptnkoj.com/submission/182209
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU, Parallel Binary Search
 *    complexity: O(n \log^2 n)
 *    note: Use DSU + PBS
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
    if(!fopen("tin_ketban.INP", "r")) return;
    freopen("tin_ketban.INP", "r", stdin);
    freopen("tin_ketban.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,m,q;
const int N = 2e5+100;

pii events[N];
int ans[N], par[N], sz[N];

struct Can{
    int u,v,id;

    Can(int _u = 0, int _v = 0, int _id = 0) : u(_u), v(_v), id(_id) {};
};

struct Roll{
    int a,b,add;

    Roll(int _a = 0, int _b = 0, int _add = 0) : a(_a), b(_b), add(_add) {};
};

vector<Roll> his;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + N, 1);
    fill(sz + 1, sz + N, 1);
    memset(ans, -1,sizeof(ans));
}

int find_set(int u){
    while(u != par[u]){
        u = par[u];
    }
    return u;
}

void union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return;

    if(sz[a] < sz[b]) swap(a,b);
    his.eb(Roll(a,b,sz[b]));
    sz[a] += sz[b];
    par[b] = a;
}

bool sameSet(int a, int b){
    return find_set(a) == find_set(b);
}

void rollback(int mark){
    while(sz(his) > mark){
        Roll tmp = his.back();
        his.pop_back();

        par[tmp.b] = tmp.b;
        sz[tmp.a] -= tmp.add;
    }
}

void solve(int l, int r, const vector<Can>& can){
    if(l > r) return;
    if(l == r){
        for(const Can& p : can) ans[p.id] = l;
        return;
    }

    int First = sz(his);    

    int mid = l + ((r-l)>>1);
    for(int i = l; i <= mid; i++){
        if(i <= m) union_set(events[i].fi,events[i].se);
    }

    vector<Can> left, right;
    left.reserve(sz(can));
    right.reserve(sz(can));

    for(const Can &p : can){
        if(sameSet(p.u,p.v)){
            left.eb(p);
        }
        else right.eb(p);
    }

    solve(mid+1,r,right);
    rollback(First);
    solve(l,mid,left);
}   

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    cin >> n >> m >> q;

    for(int i = 1; i <= m; i++){
        cin >> events[i].fi >> events[i].se;
    }

    vector<Can> queries(q);
    for(int i = 0; i < q; i++){
        cin >> queries[i].u >> queries[i].v;
        queries[i].id = i+1;
    }

    solve(1,m+1,queries);

    for(int i = 1; i <= q; i++){
        cout << (ans[i] == m+1 ? -1 : ans[i]) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}