/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-31 07:38:11
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: DÂY CUNG
 *    source: Olp_20260330
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
#include <bitset>

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
    if(!fopen("CHORDS.INP", "r")) return;
    freopen("CHORDS.INP", "r", stdin);
    freopen("CHORDS.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int bit[N];
int n;

struct Fenwick_Tree{
    void update(int pos, int val){
        for(; pos <= 2*n; pos += pos&(-pos)) bit[pos] += val;
    }
    int get(int pos){
        int ans = 0;
        for(; pos; pos -= pos&(-pos)){
            ans += bit[pos];
        }
        return ans;
    }
    int query(int l, int r){
        return get(r) - get(l-1);
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    Fenwick_Tree BIT;
    
    cin >> n;
    vpii a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].fi >> a[i].se;
        if(a[i].fi > a[i].se) swap(a[i].fi,a[i].se);
        BIT.update(a[i].fi,1);
    }
    sort(all(a,1));
    
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += BIT.query(a[i].fi+1, a[i].se);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}