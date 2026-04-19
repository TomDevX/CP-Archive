/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-17 07:01:00
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: USACO 2021 US Open, GoldUSACO 2021 US Open, Gold - Problem 1. United Cows of Farmer John
 *    source: https://usaco.org/index.php?page=viewproblem2&cpid=1137
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
    if(!fopen("1137.INP", "r")) return;
    freopen("1137.INP", "r", stdin);
    freopen("1137.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+2;
int suff[N], pref[N], a[N], pos[N], ans1[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for(int i = n; i >= 1; i--){
        if(pos[a[i]] == 0) suff[i] = n+1;
        else suff[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for(int i = 1; i <= n; i++){
        if(pos[a[i]] > i) pref[i] = 0;
        else pref[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for(int i = 1; i <= n; i++){
        update(a[i],1);
        if(suff[i] == n+1) ans1[i] = 0;
        else ans1[i] = query();
    }
    
    return NAH_I_WOULD_WIN;
}