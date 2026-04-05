/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-02 22:08:26
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Query-Sum 2
 *    source: https://lqdoj.edu.vn/problem/querysum2
 *    submission: https://lqdoj.edu.vn/submission/8335727
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Fenwick Tree (BIT)
 *    complexity: O(n \log n)
 *    note: we have Sum(1 -> p) = (p+1) * sum(d[1] -> d[p]) - sum(i*d[1] -> i*d[i]). Using diff array on Fenwick Tree (BIT)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>

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
    if(!fopen("querysum2.INP", "r")) return;
    freopen("querysum2.INP", "r", stdin);
    freopen("querysum2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
struct BIT{
    ll bit[N][2];
    int n;

    BIT(int _n = 0) : n(_n) {
        for(int i = 1; i <= n; i++) bit[i][0] = bit[i][1] = 0;
    };

    void build(vi &a){
        for(int i = 1; i <= n; i++){
            ll diff = a[i] - a[i-1];
            ll d = 1LL*i*diff;

            bit[i][0] += diff;
            bit[i][1] += d;

            int j = i + (i&-i);
            if(j <= n){
                bit[j][0] += bit[i][0];
                bit[j][1] += bit[i][1];
            }
        }
    }

    void update_point(int id, int pos, int val){
        for(;pos <= n; pos += pos&-pos){
            bit[pos][id] += val;
        }
    }

    void update_range(int l, int r, int val){
        update_point(0,l,val);
        update_point(0,r+1,-val);
        update_point(1,l,1LL*l*val);
        update_point(1,r+1,1LL*-(r+1)*val);
    }

    ll get(int pos){
        ll suma = 0, sumb = 0;
        int ori = pos;
        for(; pos; pos -= pos&-pos){
            suma += bit[pos][0];
            sumb += bit[pos][1];
        }
        return 1LL*(ori+1)*suma - sumb;
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
    
    int n,q;
    cin >> n >> q;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    BIT bit(n);
    bit.build(a);

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int l,r,val;
            cin >> l >> r >> val;
            bit.update_range(l,r,val);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << bit.query(l,r) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}