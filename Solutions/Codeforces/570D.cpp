/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-15 16:09:59
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tree Requests
 *    source: https://codeforces.com/problemset/problem/570/D
 *    submission: https://codeforces.com/problemset/submission/570/374598413
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Euler Tour, Binary Search
 *    complexity: O(n \log n)
 *    note: First we need to turn our tree into array by using Euler Tour, but if we iterate through all query's child, it would take us O(n), so we classify our nodes into arrays and store with index of its height, each time we need a height, just binary search l and r for tin[u] and tout[u], then iterate on it. Also we can make the palindrome if we have maximum 1 character from a-z to be an odd number, so just check that.
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>
#include <unordered_map>
#include <random>

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
    if(!fopen("570D.INP", "r")) return;
    freopen("570D.INP", "r", stdin);
    freopen("570D.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

int val[N], cnt[26];
int tour[N], tin[N], tout[N], h[N];
vi groupH[N];
vi adj[N];
int timer = 0;

random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<ll> dist(1,1e18);
const ll RAND = dist(gen);

struct custom_hash{
    int operator()(const pair<int,int>& x) const{
        return (x.fi*31 + x.se)^RAND;
    }
};

unordered_map<pii,bool,custom_hash> mp;

// ----------------------- [ FUNCTIONS ] -----------------------
void dfs(int u, int pre){
    tour[++timer] = u;
    tin[u] = timer;

    for(int v : adj[u]){
        if(v == pre) continue;

        h[v] = h[u] + 1;
        dfs(v,u);
    }

    tout[u] = timer;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    for(int v = 2; v  <= n; v++){
        int u;
        cin >> u;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    dfs(1,1);

    for(int i = 1; i <= n; i++){
        char c;
        cin >> c;
        val[i] = c - 'a';
    }

    for(int i = 1; i <= timer; i++){
        int u = tour[i];
        groupH[h[u]].eb(i);
    }

    while(q--){
        int u,height;
        cin >> u >> height;
        height--;

        if(mp.count({u,height})){
            cout << (mp[{u,height}] ? "Yes" : "No") << '\n';
            continue;
        }

        int l = lower_bound(all(groupH[height],0),tin[u]) - groupH[height].begin();
        int r = min(sz(groupH[height]), (int)(upper_bound(all(groupH[height],0),tout[u]) - groupH[height].begin()));

        vi &a = groupH[height];
        for(int i = l; i < r; i++){
            cnt[val[tour[a[i]]]]++;
        }

        bool has_odd = false;
        bool good = true;
        for(int i = 0; i < 26; i++){
            if(!(cnt[i]&1)) continue;

            if(has_odd){
                good = false;
                break;
            }
            has_odd = true;
        }

        mp[{u,height}] = good;
        cout << (good ? "Yes" : "No") << '\n';

        memset(cnt,0,sizeof(cnt));
    }
    
    return NAH_I_WOULD_WIN;
}