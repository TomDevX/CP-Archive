/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-21 14:37:55
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
pii st_min[N][19], st_max[N][19];
int lg[N];

// ----------------------- [ FUNCTIONS ] -----------------------
pii get_min(int l, int r){
    if(l > r) return {2e9,-1};
    int k = lg[r-l+1];
    return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}

pii get_max(int l, int r){
    if(l > r) return {-2e9,-1};
    int k = lg[r-l+1];
    return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n,q;
    cin >> n >> q;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> st_min[i][0].fi;
        st_max[i][0].fi = st_min[i][0].fi;
        st_max[i][0].se = st_min[i][0].se = i;
    }
    for(int i = 2; i <= n; i++) lg[i] = lg[i>>1] + 1;

    for(int k = 1; k <= 18; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st_min[i][k] = min(st_min[i][k-1], st_min[i + (1 << (k-1))][k-1]);
            st_max[i][k] = max(st_max[i][k-1], st_max[i + (1 << (k-1))][k-1]);
        }
    }

    while(q--){
        int l,r;
        cin >> l >> r;

        // min - min - min
        pii x = get_min(l,r);
        pii y = min(get_min(l,x.se-1), get_min(x.se+1,r));
        if(x.se > y.se) swap(x,y);
        pii z = min({get_min(l,x.se-1), get_min(x.se+1,y.se-1), get_min(y.se+1,r)});

        ll ans = 1LL*x.fi*y.fi*z.fi;

        // min - min - max
        z = max({get_max(l,x.se-1), get_max(x.se+1,y.se-1), get_max(y.se+1,r)});

        ans = min(ans, 1LL*x.fi*y.fi*z.fi);
        
        // max - max - max
        x = get_max(l,r);
        y = max(get_max(l,x.se-1), get_max(x.se+1,r));
        if(x.se > y.se) swap(x,y);
        z = max({get_max(l,x.se-1), get_max(x.se+1,y.se-1), get_max(y.se+1,r)});
        
        ans = min(ans, 1LL*x.fi*y.fi*z.fi);

        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}