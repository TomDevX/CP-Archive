/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-16 23:24:03
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Marisa Steals Reimu's Takeout
 *    source: https://codeforces.com/contest/2228/problem/A
 *    submission: https://codeforces.com/problemset/submission/2228/374887464
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(1)
 *    note: Consider all cases
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
    if(!fopen("2228A.INP", "r")) return;
    freopen("2228A.INP", "r", stdin);
    freopen("2228A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vi cnt(4);
        for(int i = 1; i <= n; i++){
            int x;
            cin >> x;
            cnt[x]++;
        }

        ll ans = cnt[0];

        if(cnt[1] >= cnt[2]){
            ans += cnt[2];
            cnt[1] -= cnt[2];
            cnt[2] = 0;

            ans += cnt[1]/3;
        }
        else{
            ans += cnt[1];
            cnt[2] -= cnt[1];

            ans += cnt[2]/3;
        }
    
        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}