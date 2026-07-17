/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-19 20:39:43
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Planets Queries I
 *    source: https://cses.fi/problemset/task/1750
 *    submission: https://cses.fi/problemset/result/16614664/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Lifting
 *    complexity: O((n+q) \log n)
 *    note: Use binary lifting, it just like sparse table and LCA, up[x][k] = node that you will go to after 2^k steps from x
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
    if(!fopen("1750.INP", "r")) return;
    freopen("1750.INP", "r", stdin);
    freopen("1750.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int up[N][32];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> up[i][0];
    }
    for(int k = 1; k <= 31; k++){
        for(int i = 1; i <= n; i++){
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }

    while(q--){
        int x,k;
        cin >> x >> k;

        for(int i = 0; i <= 31; i++){
            if(k >> i & 1) x = up[x][i];
        }
        cout << x << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}