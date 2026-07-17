/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-01 09:58:57
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: PHÍ PHÂN ĐOẠN
 *    source: https://ptnkoj.com/problem/tin_online
 *    submission: 
 *    status: WIP
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
    if(!fopen("tin_online.INP", "r")) return;
    freopen("tin_online.INP", "r", stdin);
    freopen("tin_online.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 50002;

int n;
ll P;
int a[N];
ll pref[N];
ll dp[N];
int len[N];

struct Line{
    ll m,b;
    int id;

    Line(ll _m = 0, ll _b = 0, int _id = 0) : m(_m), b(_b), id(_id) {};
} Lines[N];

deque<Line> dq;

// ----------------------- [ FUNCTIONS ] -----------------------
ll f(Line& L, ll x){
    return L.m*x + L.b;
}

int get(ll x){
    while(sz(dq) > 1 && (f(dq[0], x) > f(dq[1],x) || (f(dq[0], x) == f(dq[1],x) && len[dq[0].id] > len[dq[1].id]))){
        dq.pop_front();
    }
    return dq[0].id;
}

bool isBad(Line &L1, Line &L2, Line& L3){
    return (ld)(L2.b - L1.b)*(L2.m - L3.m) >= (ld)(L1.m - L2.m)*(L3.b - L2.b); // x1 <= x2 = good
}

void add(ll m, ll b, int id){
    Line cur = {m,b, id};
    while(sz(dq) >= 2 && isBad(dq[sz(dq) - 2], dq.back(), cur)) dq.pop_back();
    dq.push_back(cur);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> P;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }

    add(0,0,0);

    for(int i = 1; i <= n; i++){
        int best_id = get(pref[i]);
        dp[i] = f(Lines[best_id], pref[i]) + pref[i]*pref[i] + P;
        len[i] = len[best_id] + 1;
        add(-2*pref[i], dp[i] + pref[i]*pref[i], i);
        Lines[i] = {-2*pref[i], dp[i] + pref[i]*pref[i]};
    }

    cout << dp[n] << ' ' << len[n];
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