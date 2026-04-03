/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-03 10:07:43
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
const int N = 1e4+2, MAXVAL = 1e5, MOD = 5e6, K = 52;
ll dp[K][N];
ll st[K][4*MAXVAL];

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int dim, int id, int l, int r, int pos, int val){
    if(l == r){
        st[dim][id] += val;
        return;
    }

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    if(pos <= mid) update(dim,lc,l,mid,pos,val);
    else update(dim,lc|1,mid+1,r,pos,val);

    st[dim][id] = (st[dim][lc] + st[dim][lc|1])%MOD;
}

ll get(int dim, int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[dim][id];

    int mid = l + ((r-l)>>1);
    int lc = id<<1;

    return (get(dim,lc,l,mid,u,v) + get(dim,lc|1,mid+1,r,u,v))%MOD;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,k;
    cin >> n >> k;
    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        dp[1][i] = 1;
    }

    ll ans = 0;
    for(int j = 2; j <= k; j++){
        for(int i = 1; i <= n; i++){
            dp[j][i] = get(j,1,1,MAXVAL,1,a[i]-1);
            update(j,1,1,MAXVAL,a[i], dp[j-1][i]);
            if(j == k) ans = (dp[j][i] + ans)%MOD;
        }   
    }
    cout << ans;
    
    return NAH_I_WOULD_WIN;
}