/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-26 12:10:51
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Dynamic Range Sum Queries
 *    source: https://cses.fi/problemset/task/1648
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
#include <utility>
#include <cstring>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
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
    if(!fopen("1648.INP", "r")) return;
    freopen("1648.INP", "r", stdin);
    freopen("1648.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int n,q;
struct BIT{
    ll bit[N];
    
    BIT(){
        memset(bit,0,sizeof(bit));
    }

    void build(vi& a){
        for(int i = 1; i <= n; i++){
            bit[i] += a[i];
            if(i + (i & -i) <= n){
                bit[i + (i & -i)] += bit[i];
            }
        }
    }

    void update(int pos, int val){
        for(;pos <= n; pos += (pos & -pos)){
            bit[pos] += val;
        }
    }

    ll get(int pos){
        ll ans = 0;
        for(;pos; pos -= (pos & -pos)){
            ans += bit[pos];
        }
        return ans;
    }

    ll query(int l, int r){
        return get(r) - get(l-1);
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    vi a(n+1);
    BIT bit;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    bit.build(a);

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int k,u;
            cin >> k >> u;
            bit.update(k,u-a[k]);
            a[k] = u;
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << bit.query(l,r) << '\n';
        }
    }

    
    return NAH_I_WOULD_WIN;
}