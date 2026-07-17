/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-17 16:27:52
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bedao Mini Contest 27 - Mạng rễ cổ thụ
 *    source: https://oj.vnoi.info/problem/bedao_m27_e
 *    submission: https://oj.vnoi.info/submission/12757277
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Tree, Math, Inclusion-Exclusion
 *    complexity: O(m + \max(a[i]) \log \max(a[i]) \cdot \alpha(n))
 *    metacognition: Can't count gcd = 1 directly because it is very hard. Instead we can count the paths with gcd > 1 and then use exclusion to remove it out. To do that, we iterate through possible GCD values decreasing (N -> 1) and count how many paths take them as their GCD. To count how many paths take them as their GCD, we need to count the size of the componenets which all of its values divisible by GCD, and then add all the possible math through the formula size * (size-1) / 2. But now in this code I use DSU to mark the componenets so I can freely use sz[u]*sz[v] on each union for shortcuts instead of waiting for the final size (remember that paths with only 1 node counts tho). But after counting like that we're not sure if GCD is gcd of some of those paths or not, so we need to subtract out the cnt[multiplies of GCD] (exclusion). In this code I also precompute edges with divisors/gcd and nodes with divisors/gcd for easier DSU reset and calculations
 *    note: Count paths with gcd > 1 and use inclusion-exclusion on GCDs values to get gcd = 1. To count the path which take each GCD values as their gcd we use DSU and size*(size-1)/2 formula
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>
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
#define all(x,bonus) std::begin(x)+(bonus), std::end(x)
#define sub(x, st, ed) std::begin((x)) + (st), std::begin((x)) + (ed) + 1
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("bedao_m27_e.INP", "r")) return;
    freopen("bedao_m27_e.INP", "r", stdin);
    freopen("bedao_m27_e.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;

vpii edges_with_divisor[N];
vpii edges_with_gcd[N];
vi nodes_with_divisor[N];
vi nodes_with_val[N];
ll cnt[N];
int val[N];
int n;

// ----------------------- [ FUNCTIONS ] -----------------------
struct DSU{
    int par[N], sz[N];

    DSU(){
        iota(all(par,1),1);
        fill(all(sz,1),1);
    }

    void rest(int GCD){
        for(int x : nodes_with_divisor[GCD]){
            par[x] = x;
            sz[x] = 1;
        }
    }
    
    int root(int u){
        if(u == par[u]) return u;
        return par[u] = root(par[u]);
    }

    ll unite(int u, int v){
        u = root(u), v = root(v);

        // if(u == v) return 0;

        if(sz[u] < sz[v]) swap(u,v);

        int sz_u = sz[u], sz_v = sz[v];

        par[v] = u;
        sz[u] += sz[v];

        return 1LL*sz_u*sz_v;
    }
}dsu;

int gcd(int x, int y){
    while(y){
        int tmp = x%y;
        x = y;
        y = tmp;
    }
    return x;
}

ll calc(int GCD){
    ll res = sz(nodes_with_divisor[GCD]);
    for(const pii& p : edges_with_divisor[GCD]){
        res += dsu.unite(p.fi,p.se);
    }
    dsu.rest(GCD);

    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n;

    int mx = 0;
    for(int i = 1; i <= n; i++){
        cin >> val[i];
        mx = max(mx, val[i]);
        nodes_with_val[val[i]].eb(i);
    }

    for(int g = 1; g <= mx; g++){
        for(int j = g; j <= mx; j += g){
            for(int node : nodes_with_val[j]) nodes_with_divisor[g].eb(node);
        }
    }

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        
        int g = gcd(val[u], val[v]);
        edges_with_gcd[g].eb(u,v);
    }

    for(int g = 1; g <= mx; g++){
        for(int j = g; j <= mx; j += g){
            for(const pii& p : edges_with_gcd[j]) edges_with_divisor[g].eb(p);
        }
    }

    for(int i = mx; i >= 1; i--){
        cnt[i] = calc(i);
        for(int j = i << 1; j <= mx; j += i) cnt[i] -= cnt[j];
    }

    cout << cnt[1];
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}