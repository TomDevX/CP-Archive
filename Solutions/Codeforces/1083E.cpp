/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-04 21:39:54
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: The Fair Nut and Rectangles
 *    source: https://codeforces.com/contest/1083/problem/E
 *    submission: https://codeforces.com/contest/1083/submission/373523938
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Convex Hull Trick (CHT)
 *    complexity: O(n \log n)
 *    note: We notice that all x,y >= 1 and there are no nested rectangles, that means if we sort x increasing, y will be decreasing (because if it is larget than its previous rectangle, it will be a nesting case). So that we have our DP formula: dp[i] = max(j: 1 -> i-1){a[i].x*a[i].y - a[i].val + dp[j] - a[j].x*a[i].y}. So we optimize this formula by using convex hull trick with mx + b + const. 
 m = -a[i].x
 x = a[i].y
 b = dp[j]
 const = a[i].x*a[i].y - a[i].val
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
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
    if(!fopen("1083E.INP", "r")) return;
    freopen("1083E.INP", "r", stdin);
    freopen("1083E.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;

struct node{
    ll x,y,val;

    node(ll _x = 0, ll _y = 0, ll _val = 0) : x(_x), y(_y), val(_val) {};
    bool operator <(const node& o) const{
        return x < o.x;
    }
};

struct Line{
    ll m,b;

    Line(ll _m = 0, ll _b = 0) : m(_m), b(_b) {};
};

node a[N];
int n;
deque<Line> dq;

// ----------------------- [ FUNCTIONS ] -----------------------
ll f(Line L, ll x){
    return L.m*x + L.b;
}

bool isBad(const Line l1, const Line l2, const Line l3){
    return (l2.b - l1.b)*1.0L*(l2.m - l3.m) <= (l3.b - l2.b)*1.0L*(l1.m - l2.m);
}

void add(ll m, ll b){
    Line cur = Line(m,b);
    while(sz(dq) >= 2 && isBad(dq[sz(dq)-2], dq.back(), cur)) dq.pop_back();
    dq.push_back(cur);
}

ll query(ll x){
    while(sz(dq) >= 2 && f(dq[0],x) < f(dq[1],x)) dq.pop_front();
    return f(dq[0], x);
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].x >> a[i].y >> a[i].val;
    }
    sort(a + 1, a + n + 1);

    ll ans = 0;
    add(0,0);
    for(int i = 1; i <= n; i++){
        ll dp_i = query(a[i].y) + a[i].x*a[i].y - a[i].val;
        ans = max(ans, dp_i);
        add(-a[i].x, dp_i);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}