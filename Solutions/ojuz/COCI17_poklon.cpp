/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-19 07:30:12
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: COCI 2016/2017 - Contest 5 - Poklon
 *    source: https://oj.uz/problem/view/COCI17_poklon
 *    submission: https://oj.uz/submission/1355793
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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
    if(!fopen("poklon.INP", "r")) return;
    freopen("poklon.INP", "r", stdin);
    freopen("poklon.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+2;
int n,q;

int suff[N], pos[N], pos2[N], a[N], pre[N], bit[N], ans[N], sorted[N];

struct Query{
    int l,r,id;

    Query(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id) {};
    bool operator<(const Query& other){
        return l < other.l;
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int x, int val){
    for(; x <= n; x += x&-x){
        bit[x] += val;
    }
}

int get(int x){
    int res = 0;
    for(; x ; x -= x&-x) res += bit[x];
    return res;
}

int query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i<= n; i++) cin >> a[i], sorted[i] = a[i];
    sort(sorted + 1, sorted + n + 1);
    for(int i = 1; i <= n; i++) a[i] = lower_bound(sorted + 1, sorted + n + 1, a[i]) - sorted;

    for(int i = 1; i <= n; i++) suff[i] = n+1, pos[a[i]] = pos2[a[i]] = n+1;
    for(int i = n; i >= 1; i--){
        if(pos[a[i]] && pos2[a[i]]) suff[i] = pos2[a[i]];
        pos2[a[i]] = pos[a[i]];
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    
    for(int i = 1; i <= n; i++){
        if(pos[a[i]] == i){
            update(pre[i], 1);
            update(suff[i], -1);
        }
    }
    
    vector<Query> queries(q+1);
    
    for(int i = 1; i <= q; i++){
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(all(queries,1));

    int cur = 1;

    for(int i = 1; i <= q; i++){
        for(; cur < queries[i].l; cur++){
            if(pre[cur] > 0) update(pre[cur], -1);
            update(suff[cur], 2);
            if(pre[suff[cur]] > 0) update(pre[suff[cur]], -1);
        }
        ans[queries[i].id] = query(queries[i].l, queries[i].r);
    }
    
    for(int i = 1; i <= q; i++){
        cout << ans[i] << '\n';
    }

    return NAH_I_WOULD_WIN;
}