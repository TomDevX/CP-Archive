/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-03-21 23:40:47
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: String occurences 2 - Hash Approach
 *    source: https://marisaoj.com/problem/165
 *    submission: https://marisaoj.com/submission/1132007
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hashing
 *    complexity: O(n+m)
 *    note: Use typical Hashing algorithm
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

using namespace std;

// --- [ DEBUGGING & LOCAL CONFIG ] ---
#if __has_include("TomDev.h")
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
    if(!fopen("165.INP", "r")) return;
    freopen("165.INP", "r", stdin);
    freopen("165.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+2;
const ll MOD = 1e9+6967;
ll hashS[N];
ll hashT = 0;
int base = 31;
ll POW[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void init(){
    POW[0] = 1;
    for(int i = 1; i < N; i++){
        POW[i] = (POW[i-1]*base)%MOD;
    }
}

ll get_hash(int l, int r){
    return ((hashS[r] - hashS[l-1]*POW[r-l+1])%MOD + MOD)%MOD;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    init();
    
    string s,t;
    cin >> s >> t;

    int n = sz(s), m = sz(t);
    s = '#' + s;
    t = '#' + t;

    for(int i = 1; i <= n; i++){
        hashS[i] = (hashS[i-1]*base + s[i] - '0' + 1)%MOD;
    }

    for(int i = 1; i <= m; i++){
        hashT = (hashT*base + t[i] - '0' + 1)%MOD;
    }

    int ans = 0;
    for(int i = m; i <= n; i++){
        if(get_hash(i - m + 1, i) == hashT) ans++;
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}