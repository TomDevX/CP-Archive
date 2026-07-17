/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-14 13:48:44
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: MỞ QUÀ
 *    source: https://ptnkoj.com/problem/tin_gift
 *    submission: https://ptnkoj.com/submission/182094
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Convex Hull Trick
 *    complexity: O(n)
 *    note: Typical DP CHT
**/

#include <iostream>
#include <vector>
#include <algorithm>    
#include <cstdio>
#include <utility>
#include <deque>

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
    if(!fopen("tin_gift.INP", "r")) return;
    freopen("tin_gift.INP", "r", stdin);
    freopen("tin_gift.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;

ll pref[N];
ll dp[N];
int a[N];
deque<pll> dq;


// ----------------------- [ FUNCTIONS ] -----------------------
ll f(ll m, ll b, ll x){
    return m*x + b;
}

bool bad(pll l1, pll l2, pll l3){
    return (l2.se - l1.se)*(l2.fi - l3.fi) >= (l3.se - l2.se)*(l1.fi - l2.fi);
}

void add(ll m, ll b){
    pll l3 = {m,b};
    while(sz(dq) >= 2 && bad(dq[sz(dq)-2], dq.back(), l3)){
        dq.pop_back();
    }
    dq.push_back(l3);
}

ll query(ll x){
    while(sz(dq) >= 2 && f(dq[0].fi, dq[0].se, x) >= f(dq[1].fi, dq[1].se,x)){
        dq.pop_front();
    }
    return f(dq[0].fi,dq[0].se,x);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();

    int n;
    ll C;
    cin >> n >> C;
    for(int i = 1; i <= n; i++) cin >> a[i], pref[i] = a[i] + pref[i-1];

    dp[0] = 0;
    add(0, 0);
    for(int i = 1; i <= n; i++){
        dp[i] = query(pref[i]) + (pref[i]*pref[i]) + C;
        add(-2*pref[i], dp[i] + pref[i]*pref[i]);
    }

    cout << dp[n];
    
    return NAH_I_WOULD_WIN;
}