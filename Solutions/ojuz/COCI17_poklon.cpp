/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-19 07:30:12
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: COCI 2016/2017 - Contest 5 - Poklon
 *    source: https://oj.uz/problem/view/COCI17_poklon
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
    if(!fopen("COCI17_poklon.INP", "r")) return;
    freopen("COCI17_poklon.INP", "r", stdin);
    freopen("COCI17_poklon.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+2;
int n,q;

int pref[N], suff[N], pos[N], pos2[N], a[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    cin >> n >> q;
    for(int i = 1; i<= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++){
        if(pos[a[i]] && pos2[a[i]]) pref[i] = pos2[a[i]];
        pos2[a[i]] = pos[a[i]];
        pos[a[i]] = i;
    }

    for(int i = 1; i <= n; i++) suff[i] = n+1, pos[a[i]] = pos2[a[i]] = 0;
    for(int i = n; i >= 1; i--){
        if(pos[a[i]] && pos2[a[i]]) suff[i] = pos2[a[i]];
        pos2[a[i]] = pos[a[i]];
        pos[a[i]] = i;
    }

    
    
    return NAH_I_WOULD_WIN;
}