/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-05 21:31:13
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: ILSBIN
 *    source: https://oj.vnoi.info/problem/ilsbin
 *    submission: https://oj.vnoi.info/submission/12248000
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DSU, Math
 *    complexity: O(n \alpha (n))
 *    note: Turn this problem into a prefix sum, if pref[r] - pref[l-1] = odd => parity(pref[r]) != parity(pref[l-1]), if = even => parity(pref[r]) = parity(pref[l-1]). To make sure these 2 conditions satisfies at an ith query, we create opposite of l >< _l and r >< _r, so if odd => parity(r) = parity(_l), even => parity(r) = parity(l). So every time we need to make sure the opposite does not have the same condition (hard to understand but just take a look at the code below)
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
    if(!fopen("ilsbin.INP", "r")) return;
    freopen("ilsbin.INP", "r", stdin);
    freopen("ilsbin.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int M = 5002, N = M*4;

string type[M];
int L[M], R[M], par[N], sz[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    iota(par, par + N, 0);
    fill(sz, sz + N, 1);
}

int find_set(int u){
    if(u == par[u]) return u;
    return par[u] = find_set(par[u]);
}

void unite(int a, int b){
    a = find_set(a), b = find_set(b);
    if(a  == b) return;

    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    int n,m;
    cin >> n;
    cin >> m;

    vi a;
    a.reserve(N);

    for(int i = 1; i <= m; i++){
        cin >> L[i] >> R[i] >> type[i];
        a.eb(L[i]-1);
        a.eb(R[i]);
    }
    sort(all(a,0));

    for(int i = 1; i <= m; i++){
        int l = lower_bound(all(a,0), L[i]-1) - a.begin() + 1; // -1 because pref[r] - pref[l-1]
        int _l = l + sz(a);
        int r = lower_bound(all(a,0), R[i]) - a.begin() + 1;
        int _r = r + sz(a);

        l = find_set(l);
        r = find_set(r);
        _l = find_set(_l);
        _r = find_set(_r);

        if(type[i] == "odd"){
            if(r == l || _r == _l){ // if (r and l) or (_r and _l) has same parity before, this condition fails because they must have opposite parity
                cout << i-1;
                return 0;
            }
            unite(r,_l);
            unite(_r,l);
        }
        else{
            if(r == _l || _r == l){ // if (r and _l) or (_r and l) has same parity before, this condition fails because they must have opposite parity
                cout << i-1;
                return 0;
            }
            unite(r,l);
            unite(_r,_l);
        }
    }

    cout << m;
    
    return NAH_I_WOULD_WIN;
}