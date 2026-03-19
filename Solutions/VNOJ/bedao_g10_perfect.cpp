/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-19 21:47:22
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Bedao Grand Contest 10 - PERFECT
 *    source: https://oj.vnoi.info/problem/bedao_g10_perfect
 *    submission: https://oj.vnoi.info/submission/11912847
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Sparse Table, RMQ
 *    complexity: O(n \log n)
 *    note: There's a cool trick of permutation to check if it is consecutive or not is if the different between max value and min value in that permutation = size of permutation, so it is consecutive. In this problem, we use sparse table to query the min and max value in [l;r]
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
    if(!fopen("bedao_g10_perfect.INP", "r")) return;
    freopen("bedao_g10_perfect.INP", "r", stdin);
    freopen("bedao_g10_perfect.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
int st_min[N][18], st_max[N][18];
int lg[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int get_max(int l, int r){
    int k = lg[r-l+1];
    return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
}
int get_min(int l, int r){
    int k = lg[r-l+1];
    return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++){
        cin >> st_min[i][0];
        st_max[i][0] = st_min[i][0];
    }
    for(int i = 2; i <= n; i++) lg[i] = lg[i>>1] + 1;

    for(int k = 1; k <= 17; k++){
        for(int i = 1; i + (1 << k) - 1 <= n; i++){
            st_min[i][k] = min(st_min[i][k-1], st_min[i + (1 << (k-1))][k-1]);
            st_max[i][k] = max(st_max[i][k-1], st_max[i + (1 << (k-1))][k-1]);
        }
    }

    while(q--){
        int l,r;
        cin >> l >> r;

        // dbg(get_max(l,r), get_min(l,r));
        cout << (get_max(l,r) - get_min(l,r) == r - l ? "YES" : "NO" ) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}