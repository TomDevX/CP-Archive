/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-17 21:39:59
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: MOMOS - FEASTOFPIGS
 *    source: https://oj.vnoi.info/problem/gogovoi_momos
 *    submission: https://oj.vnoi.info/submission/12760950
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Inclusion-Exclusion
 *    complexity: O(n \log n + 2^n)
 *    metacognition: Make it into 2 cases, iterate through multipliers with n <= 1e6 and inclusion-exclusion with n <= 1e14 cuz k <= 20. Remember to use backtrack cutting branch to reduce the LCM operations
 *    note: Using sieve multipliers check for n <= 1e6 and inclusion-exclusion with backtracking cutting branch with n <= 1e14
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
    if(!fopen("gogovoi_momos.INP", "r")) return;
    freopen("gogovoi_momos.INP", "r", stdin);
    freopen("gogovoi_momos.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2, K = 102;

ll n;
int k;
int a[K];

// ----------------------- [ FUNCTIONS ] -----------------------
ll gcd(ll x, ll y){
    while(y){
        ll tmp = x%y;
        x = y;
        y = tmp;
    }
    return x;
}

ll lcm(ll x, ll y){
    if(x / gcd(x,y) > (n + y - 1)/y) return n+1;
    return x / gcd(x,y) * y;
}

namespace sub1{
    bool check(){
        return n <= 1e6 && k <= 100;
    }
    void solve(){
        static bitset<N> vis;
        for(int i = 1; i <= k; i++){
            for(int j = a[i]; j <= n; j += a[i]) vis[j] = 1;
        }

        cout << n-vis.count();
    }
}

namespace sub2{
    ll ans = 0;
    bool check(){
        return n <= 1e14 && k <= 20;
    }
    void backtrack(int idx, int cnt, ll LCM){
        if(idx > k){
            if(cnt == 0 || LCM > n) return;

            if(cnt&1) ans += n/LCM;
            else ans -= n/LCM;
            return;
        }

        backtrack(idx+1,cnt,LCM);
        LCM = lcm(LCM, a[idx]);
        if(LCM < n) backtrack(idx+1,cnt+1,LCM);
    }
    void solve(){
        backtrack(1,0,1);

        cout << n-ans;
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> k;
    n--;
    for(int i = 1; i <= k; i++) cin >> a[i];
    
    if(sub1::check()) return sub1::solve();
    return sub2::solve();
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