/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-01 09:10:28
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: CẮT DÃY
 *    source: https://ptnkoj.com/problem/tin_catday
 *    submission: https://ptnkoj.com/submission/182667
 *    status: AC
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
 *    note: 
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <deque>
#include <cstring>

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
    if(!fopen("tin_catday.INP", "r")) return;
    freopen("tin_catday.INP", "r", stdin);
    freopen("tin_catday.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5002;

ll dp[2][N], pref[N];
int a[N];
int n,k;

struct Line{
    ll m,b;
};

deque<Line> dq;

// ----------------------- [ FUNCTIONS ] -----------------------
void rest(){
    dq.clear();
}

ll f(Line& L, ll x){
    return L.m*x + L.b;
}

ll get(ll x){
    while(sz(dq) > 1 && f(dq[0], x) > f(dq[1],x)){
        dq.pop_front();
    }
    return f(dq[0],x);
}

bool isBad(Line &L1, Line &L2, Line& L3){
    return (ld)(L2.b - L1.b)*(L2.m - L3.m) - (ld)(L1.m - L2.m)*(L3.b - L2.b) >= 0; // x1 <= x2
}

void add(ll m, ll b){
    Line cur = {m,b};
    while(sz(dq) >= 2 && isBad(dq[sz(dq) - 2], dq.back(), cur)) dq.pop_back();
    dq.push_back(cur);
}

void solve(int idx, int cur){
    add(-2*pref[cur-1], dp[!idx][cur-1] + pref[cur-1]*pref[cur-1]);
    for(int i = cur; i <= n; i++){
        dp[idx][i] = get(pref[i]) + pref[i]*pref[i];
        if(cur != 1) add(-2*pref[i], dp[!idx][i] + pref[i]*pref[i]); // can't divide 0 segments with any i elements
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> k;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }

    int idx = 1;
    for(int i = 1; i <= k; i++){
        solve(idx,i);
        rest();
        dbg(dp[idx][n],i);
        idx = !idx;
    }

    cout << dp[!idx][n];
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