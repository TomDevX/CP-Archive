/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-11 18:21:59
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Splitting a Rope
 *    source: https://atcoder.jp/contests/awc0066/tasks/awc0066_d
 *    submission: https://atcoder.jp/contests/awc0066/submissions/75727624
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Binary Search
 *    complexity: O(n \cdot value \log (n \cdot value))
 *    note: Just binary search on the max value for each group
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
    if(!fopen("awc0066_d.INP", "r")) return;
    freopen("awc0066_d.INP", "r", stdin);
    freopen("awc0066_d.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

int a[N];
int n,k;

// ----------------------- [ FUNCTIONS ] -----------------------
bool check(ll x){
    int cnt = 1;
    ll sum = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] > x) return false;
        sum += a[i];
        if(sum > x){
            sum = a[i];
            cnt++;
        }
    }

    return cnt <= k;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];

    ll l = 0, r = 1e14;
    ll ans = 1e9;
    while(l <= r){
        ll mid = l + ((r-l)>>1LL);

        if(check(mid)){
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}