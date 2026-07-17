/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-17 20:45:28
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Propagating tree
 *    source: https://codeforces.com/problemset/problem/383/C
 *    submission: https://codeforces.com/contest/383/submission/374956458
 *    status: AC
 * ----------------------------------------------------------
 *    tags: BIT, Euler Tour, Math
 *    complexity: O(n \log n)
 *    note: So we notice that if that node has the same parity with u, it will get +val, else it will get -val. So how do we manage it? First we rule that parity of odd will get -val, and even will get +val. So when querying how do we know the correct answer? -> If the queried v node has parity of odd, we return -pref[v], else if even, return pref[u]. Why? Let's take an example that u is odd, and we -val to [tin[u], tout[u]]. And now v is odd too, so we turn answer to -pref[v] -> -(-val) = val, it returns to normal. If v is even, we don't switch the sign(v) so it is still -pref[v] => if not the same parity, it will get sign(-), else, we'll still get sign(+)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("383C.INP", "r")) return;
    freopen("383C.INP", "r", stdin);
    freopen("383C.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

int bit[N], a[N];
vi adj[N];
int tin[N], tout[N];
bitset<N> parity;

int timer = 0;

int n;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tin[u] = ++timer;
    parity[u] = !parity[pre];

    for(int v : adj[u]){
        if(v == pre) continue;

        dfs(v,u);
    }

    tout[u] = timer;
}

void update(int pos, int val){
    for(; pos <= n; pos += pos&-pos) bit[pos] += val;
}

void update_range(int l, int r, int val){
    update(l,val);
    update(r+1,-val);
}

int get(int pos){
    int res = 0;
    for(; pos; pos -= pos&-pos) res += bit[pos];
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    
    dfs(1,0);

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int u,val;
            cin >> u >> val;

            if(!parity[u]) val = -val;   

            update_range(tin[u], tout[u],val);
        }   
        else{
            int u;
            cin >> u;

            int ans = get(tin[u]);

            cout << a[u] + (parity[u] ? ans : -ans) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}