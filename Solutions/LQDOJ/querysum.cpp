/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-01 09:57:42
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Query-Sum
 *    source: https://lqdoj.edu.vn/problem/querysum
 *    submission: https://lqdoj.edu.vn/submission/8320846
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Fenwick Tree
 *    complexity: O(n \log n)
 *    note: Typical Fenwick Tree
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
    if(!fopen("querysum.INP", "r")) return;
    freopen("querysum.INP", "r", stdin);
    freopen("querysum.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
struct BIT{
    ll bit[N];
    int n;

    BIT(int _n = 0) : n(_n) {
        memset(bit,0,sizeof(bit));
    };

    void build(const vi& a){
        for(int i = 1; i <= n; i++){
            bit[i] += a[i];

            int j = i + (i&-i);
            if(j <= n) bit[j] += bit[i];
        }
    }

    void update(int pos, int val){
        for(; pos <= n; pos += pos&-pos){
            bit[pos] += val;
        }
    }

    ll prefSum(int pos){
        ll ans = 0;
        for(; pos; pos -= pos&-pos){
            ans += bit[pos];
        }
        return ans;
    }

    ll query(int l, int r){
        return prefSum(r) - prefSum(l-1);
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
            int pos,x;
            cin >> pos >> x;

            bit.update(pos,x);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << bit.query(l,r) << '\n';
        }
    }

    return NAH_I_WOULD_WIN;
}