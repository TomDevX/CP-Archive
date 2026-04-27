/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-27 16:02:35
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Color query
 *    source: https://oj.vnoi.info/problem/colquery
 *    submission: https://oj.vnoi.info/submission/12195450
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU
 *    complexity: O(q \log n \alpha(n))
 *    note: Use map to count colors, also use small-to-large merging to reduce the time complexity. We can't use multiset because when it calculate the distance between upper_bound and lower_bound, it will get TLE cuz it's O(n)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <unordered_map>
#include <numeric>
#include <iterator>

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
    if(!fopen("colquery.INP", "r")) return;
    freopen("colquery.INP", "r", stdin);
    freopen("colquery.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int c[N];

int par[N];
unordered_map<int,int> colors[N]; // u can use map too but I'd like to take some risks
int n,q;

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par + 1, par + n + 1, 1);
    for(int i = 1; i <= n; i++) colors[i][c[i]]++;
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

void union_set(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a == b) return;

    if(sz(colors[a]) < sz(colors[b])) swap(a,b);
    for(const pair<int,int> &p : colors[b]) colors[a][p.fi] += p.se;
    par[b] = a;
    unordered_map<int,int>().swap(colors[b]); // just some release for our unused memory
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> c[i];
    init();

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int a,b;
            cin >> a >> b;
            union_set(a,b);
        }
        else{
            int u,col;
            cin >> u >> col;
            u = find_set(u);

            if(colors[u].count(col)) cout << colors[u][col] << '\n';
            else cout << "0\n";
        }
    }
    
    return NAH_I_WOULD_WIN;
}