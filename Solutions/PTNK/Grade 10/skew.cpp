/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-08 09:42:45
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phân chia lệch
 *    source: DT 08-06-2026.pdf
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("skew.INP", "r")) return;
    freopen("skew.INP", "r", stdin);
    freopen("skew.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5+5;

int a[N];
ll pref[N];
int prefmin[N], suffmin[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,k;
    cin >> n >> k;

    for(int i = 1; i <= n; i++) cin >> a[i];
    fill(sub(prefmin,0,n+1), 1e9);
    fill(sub(suffmin,0,n+1), 1e9);

    for(int i = 1; i <= n; i++){
        pref[i] = pref[i-1] + a[i];
        prefmin[i] = min(prefmin[i-1], a[i]);
    }

    for(int i = n; i >= 1; i--){
        suffmin[i] = min(suffmin[i+1], a[i]);
    }

    int big_size = n-k+1;

    ll ans = 0;
    for(int i = big_size; i <= n; i++){
        ans = max(ans, pref[i] - pref[i-big_size] - min(prefmin[i-big_size], suffmin[i+1]));
    }
    cout << ans << '\n';
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