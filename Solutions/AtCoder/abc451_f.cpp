/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-09 22:07:29
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Make Bipartite 3
 *    source: https://atcoder.jp/contests/abc451/tasks/abc451_f
 *    submission: https://atcoder.jp/contests/abc451/submissions/75678817
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(q \alpha (n))
 *    note: So we make the root as the one node that determine our color. Each query, if u and v are not in the same component (check by DSU), it will be always bipartite, so we just need to determine if v after combining into u will be the same parity with root_u or not, if same, we add the same parity from 2 compoenents together, else, we add opposite parity from 2 componenets. If u and v in the same componenets and it has the same parity, that is the death sentence and the ans will be -1.
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
    if(!fopen("abc451_f.INP", "r")) return;
    freopen("abc451_f.INP", "r", stdin);
    freopen("abc451_f.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int par[N], sz[N], dis[N], cnt0[N], cnt1[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(sub(par,1,N-1),1);
    fill(sub(sz,1,N-1),1);
    fill(sub(cnt0,1,N-1),1);
}

pii root(int u){
    if(u == par[u]) return {u,0};
    pii Root = root(par[u]);
    par[u] = Root.fi;
    dis[u] += Root.se;
    return {par[u],dis[u]};
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,q;
    cin >> n >> q;

    int ans = 0;
    while(q--){
        int u,v;
        cin >> u >> v;
        int ru = root(u).fi, rv = root(v).fi;
        if(sz[ru] < sz[rv]) swap(ru,rv), swap(u,v);

        if(ru == rv){
            if((dis[u]&1) == (dis[v]&1)){
                ans = -1;
            }
        }
        else if(ans != -1){
            ans -= min(cnt0[ru],cnt1[ru]) + min(cnt0[rv],cnt1[rv]);

            int w = dis[u] + dis[v] + 1;
            dis[rv] = w;
            if(!(w&1)){
                cnt0[ru] += cnt0[rv];
                cnt1[ru] += cnt1[rv];
            }
            else{
                cnt0[ru] += cnt1[rv];
                cnt1[ru] += cnt0[rv];
            }
            par[rv] = ru;
            sz[ru] += sz[rv];

            ans += min(cnt0[ru], cnt1[ru]);
        }
        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}