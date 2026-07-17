/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-05 15:12:29
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: THU THẬP
 *    source: https://ptnkoj.com/problem/tin_thuthap
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
    if(!fopen("tin_thuthap.INP", "r")) return;
    freopen("tin_thuthap.INP", "r", stdin);
    freopen("tin_thuthap.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+100;

int n,m,k;

vi poss[N];
ll bit[N], target[N];
int ans[N];

struct Query{
    int l,r,x,id;

    Query(int _l = 0, int _r = 0, int _x = 0, int _id = 0) : l(_l), r(_r), x(_x), id(_id) {};
};

Query queries[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int pos, ll val){
    for(; pos <= m; pos += pos&-pos) bit[pos] += val;
}

ll query(int pos){
    ll res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

void update_range(int id, int sign){
    int l = queries[id].l, r = queries[id].r, x = queries[id].x;
    if(l <= r){
        update(l,x*sign);
        update(r+1,-x*sign);
    }
    else{
        update(l,x*sign);
        update(1,x*sign);
        update(r+1,-x*sign);
    }
}

ll get_tot(int x){
    ll res = 0;
    for(int pos : poss[x]){
        res += query(pos);
        if(res >= target[x]) return res;
    }
    return res;
}

void rollback(int l, int r){
    for(int i = l; i <= r; i++){
        update_range(i,-1);
    }
}

void solve(int l, int r, const vi& can){
    if(l == r){
        for(int x : can) ans[x] = l;
        return;
    }

    int mid = l + ((r-l)>>1);

    for(int i = l; i <= mid; i++){
        if(i <= k) update_range(i,1);
    }

    vi left,right;
    left.reserve(sz(can));
    right.reserve(sz(can));

    for(int x : can){
        ll tot = get_tot(x);
        if(tot >= target[x]) left.eb(x);
        else{
            right.eb(x);
            target[x] -= tot;
        }
    }

    rollback(l,mid);
    solve(mid+1,r,right);
    solve(l,mid,left);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int x;
        cin >> x;
        poss[x].eb(i);
    }

    vi a(n);
    for(int i = 1; i <= n; i++){
        a[i-1] = i;
        cin >> target[i]; 
    }

    cin >> k;

    for(int i = 1; i <= k; i++){
        cin >> queries[i].l >> queries[i].r >> queries[i].x;
        queries[i].id = i;
    }

    solve(1,k+1,a);

    for(int i = 1; i <= n; i++) cout << (ans[i] == k + 1 ? -1 : ans[i]) << '\n';
    
    return NAH_I_WOULD_WIN;
}