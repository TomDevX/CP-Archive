/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-15 18:43:16
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Distinct Values Queries
 *    source: https://cses.fi/problemset/task/1734
 *    submission: https://cses.fi/problemset/result/16918559/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BIT, Distinct Value
 *    complexity: O(n \log n)
 *    note: Mark our bit array as 1 if that position is the first emergence of that value. Sort the queries by l increasing, to get result, just get sum of 1s from l -> r, to remove, make a suffix array to store the nearest index of value on the right
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
    if(!fopen("1734.INP", "r")) return;
    freopen("1734.INP", "r", stdin);
    freopen("1734.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;

int pos[N], suff[N], a[N], bit[N], ans[N], sorted[N];
int n,q;

struct Query{
    int l,r, id;

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
    for(; x; x -= x&-x) res += bit[x];
    return res;
}

int query(int l, int r){
    return get(r) - get(l-1);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;

    for(int i = 1; i <= n; i++) cin >> a[i], sorted[i] = a[i];
    sort(sorted + 1, sorted + n + 1);
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(sorted + 1, sorted + n + 1, a[i]) - sorted;
    }

    cin >> q;

    for(int i = n; i >= 1; i--){
        if(pos[a[i]] == 0) suff[i] = n+1;
        else suff[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    vector<Query> queries(q+1);
    for(int i = 1; i <= q; i++){
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(all(queries,1));

    for(int i = 1; i <= n; i++){
        if(pos[a[i]] == i) update(i,1);
    }

    int cur = 1;
    for(int i = 1; i <= q; i++){
        for(; cur < queries[i].l; cur++){
            update(suff[cur],1);
        }

        ans[queries[i].id] = query(queries[i].l,queries[i].r);
    }

    for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
    
    return NAH_I_WOULD_WIN;
}