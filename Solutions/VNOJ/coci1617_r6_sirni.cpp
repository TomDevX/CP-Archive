/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-07 23:30:07
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: COCI 2016/2017 - Contest 6 - Sirni
 *    source: https://oj.vnoi.info/problem/coci1617_r6_sirni
 *    submission: https://oj.vnoi.info/submission/12259781
 *    status: AC
 * ----------------------------------------------------------
 *    tags: MST, Math
 *    complexity: O(M \log M + N \log N)
 *    note: Ok so first we notice that if 2 elements share the same value, the cost will be 0, so we skip it by filtering unique. Now assume val[a] < val[b], so it is obvious that min(Pa % Pb, Pb % Pa) = Pb % Pa. So now we will be iterating through elements and sieve for its multiples and check if it is available in the array. First we need to initialize the nxt array first to track the nearest number on the right to that number which is available in our given array. So now when we're at a[i]'s multiple, we check for the nearest with nxt array to minimize the modulo, then add it to the edges arrays. Finally, Kruskal on that edge array (use counting or bucket sort instead of adding modulo value to it and use sort() again to reduce some time complexity)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>

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
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
#define filter(x,bonus) (x).erase(unique(std::begin((x))+(bonus), std::end((x))), std::end((x)))
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
    if(!fopen("coci1617_r6_sirni.INP", "r")) return;
    freopen("coci1617_r6_sirni.INP", "r", stdin);
    freopen("coci1617_r6_sirni.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
vi par, sz;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(int n){
    iota(sub(par,1,n),1);
    fill(sub(sz,1,n), 1);
}

int root(int u){
    if(u == par[u]) return u;
    return par[u] = root(par[u]);
}

bool unite(int a, int b){
    a = root(a), b = root(b);
    if(a == b) return false;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;

    return true;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    par.resize(n+1);
    sz.resize(n+1);
    
    vi a(n+1);
    int maxv = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        maxv = max(maxv,a[i]);
    }
    
    sort(all(a,1));
    filter(a,1);
    
    vector<vpii> cost(maxv+1);
    vi nxt(maxv+1);
    
    n = sz(a)-1;
    for(int i = 1; i <= n; i++){
        nxt[a[i]] = i;    
    }
    for(int i = maxv-1; i >= 1; i--){
        if(nxt[i] == 0) nxt[i] = nxt[i+1];
    }
    init(n);
    

    for(int i = 1; i < n; i++){
        cost[a[i+1]%a[i]].eb(i,i+1);
        for(int j = a[i]<<1; j <= maxv;){
            int pos = nxt[j];
            if(!pos) break;
            cost[a[pos]%a[i]].eb(i,pos);

            j = (a[pos] / a[i] + 1) * a[i];
        }
    }

    ll ans = 0;

    for(int i = 0; i < maxv; i++){
        for(const pii& p : cost[i]){
            if(unite(p.fi,p.se)) ans += i;
        }
    }

    cout << ans;

    return NAH_I_WOULD_WIN;
}