/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-14 14:49:24
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: KHAI THÁC KHOÁNG SẢN
 *    source: https://ptnkoj.com/problem/tin_mine
 *    submission: https://ptnkoj.com/submission/182149
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Convex Hull Trick
 *    complexity: O(n)
 *    note: Another Typical DP Convex Hull Trick but this time we get the max value
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
    if(!fopen("tin_mine.INP", "r")) return;
    freopen("tin_mine.INP", "r", stdin);
    freopen("tin_mine.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;
int a[N];
ll pref[N], dp[N];

ll heso[4];

struct node{
    ll m, b;

    node(ll _m = 0, ll _b = 0) : m(_m), b(_b) {};
};

deque<node> dq;
// ----------------------- [ FUNCTIONS ] -----------------------
bool bad(const node& l1, const node& l2, const node& l3){
    return (l2.b - l1.b)*(l2.m - l3.m) >= (l1.m - l2.m)*(l3.b - l2.b);
}

ll f(ll m, ll b, ll x){
    return m*x + b;
}

void add(ll m, ll b){
    node l3 = node(m,b);

    while(sz(dq) >= 2 && bad(dq[sz(dq)-2], dq.back(), l3)) dq.pop_back();

    dq.push_back(l3);
}

ll query(ll x){
    while(sz(dq) >= 2 && f(dq[0].m, dq[0].b, x) <= f(dq[1].m, dq[1].b, x)) dq.pop_front();
    return f(dq[0].m,dq[0].b,x);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= 3; i++) cin >> heso[i];
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pref[i] = a[i] + pref[i-1];
    }

    dp[0] = 0;
    add(0,0);
    for(int i = 1; i <= n; i++){
        dp[i] = query(pref[i]) + heso[1]*pref[i]*pref[i] + heso[2]*pref[i] + heso[3];
        add(-2*heso[1]*pref[i], heso[1]*pref[i]*pref[i] - heso[2]*pref[i] + dp[i]);
    }

    cout << dp[n];
    
    return NAH_I_WOULD_WIN;
}