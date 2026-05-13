/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-11 18:10:13
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Smartphone Battery
 *    source: https://atcoder.jp/contests/awc0066/tasks/awc0066_b
 *    submission: https://atcoder.jp/contests/awc0066/submissions/75727255
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Implementation
 *    complexity: O(n \log n)
 *    note: Just sort then give the phones which are about to die most the charger
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>

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
    if(!fopen("awc0066_b.INP", "r")) return;
    freopen("awc0066_b.INP", "r", stdin);
    freopen("awc0066_b.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,l,k,y;
    cin >> n >> l >> k >> y;

    vi a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    sort(all(a,1));
    int idx = 1;
    int cnt = 0;
    for(; idx <= n && k; idx++){
        if(a[idx] <= l) continue;
        k--;
        cnt++;
    }

    for(int i = idx; i <= n; i++){
        if(a[i] - y > l) cnt++;
    }
    cout << cnt;
    
    return NAH_I_WOULD_WIN;
}