/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-07 21:04:41
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
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
    if(!fopen("test.INP", "r")) return;
    freopen("test.INP", "r", stdin);
    freopen("test.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
int n,q;
const int N = 1e5+2;
struct Query{
    int l,r,rang,val;

    Query(int _l = 0, int _r = 0, int _rang = 0, int _val = 0) : l(_l), r(_r), rang(_rang), val(_val) {};
};
Query queries[N];

struct BITR{
    ll bit[N][2];
    int n;

    BITR(int _n = 0) : n(_n) {
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
        update_point(0,r+1,-val*(r-l));
        update_point(1,l,1LL*l*val);
        update_point(1,r+1,1LL*-(r+1)*val*(r-l));
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
namespace subtask1{
    bool check(){
        for(int i = 1; i <= q; i++){
            if(queries[i].l != queries[i].r) return false;
        }
        return true;
    }

    void solve(){
        vll a(n+1);
        for(int i = 1; i <= q; i++){
            a[queries[i].l] += queries[i].val;
        }
        for(int i = 1; i <= n; i++) cout << a[i] << ' ';
    }
}

namespace subtask2{
    bool check(){
        for(int i = 1; i <= q; i++){
            if(queries[i].rang != 1) return false;
        }
        return true;
    }

    void solve(){
        vll a(n+1);
        for(int i = 1; i <= q; i++){
            a[queries[i].l] += queries[i].val;
            a[queries[i].r+1] -= (queries[i].r+1)*queries[i].val;
        }
        for(int i = 1; i <= n; i++){
            a[i] += a[i-1];
            cout << a[i] << ' ';
        }
    }
}

namespace subtask3{
    void solve(){
        vll a(n+1);
        for(int i = 1; i <= q; i++){
            int cnt = 0;
            for(int j = queries[i].l; j <= queries[i].r; j += queries[i].rang){
                a[j] += (cnt+1)*queries[i].val;
                cnt++;
            }
        }
        for(int i = 1; i <= n; i++) cout << a[i] << ' ';
    }
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i <= q; i++){
        cin >> queries[i].l >> queries[i].r >> queries[i].rang >> queries[i].val;
    }

    if(subtask1::check()) return subtask1::solve(),0;
    if(subtask2::check()) return subtask2::solve(),0;
    subtask3::solve();
    
    return NAH_I_WOULD_WIN;
}
