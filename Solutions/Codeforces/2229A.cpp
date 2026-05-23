/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 21:36:04
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Slimes on a Line
 *    source: https://codeforces.com/contest/2229/problem/A
 *    submission: https://codeforces.com/contest/2229/submission/375784609
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n)
 *    note: Because we need to get the max distance so our only needed number is max and min number, just get the mid of it and it will be the most optimized
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cmath>

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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("2229A.INP", "r")) return;
    freopen("2229A.INP", "r", stdin);
    freopen("2229A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------


// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;

    int n;
    while(tc--){
        cin >> n;
        vi a(n+1);
        int minn = 1e9, maxn = 0;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            minn = min(minn, a[i]);
            maxn = max(maxn, a[i]);
        }

        int mid = minn + ((maxn - minn)>>1);
        int ans = 0;

        for(int i = 1; i <= n; i++){
            ans = max(ans, abs(mid - a[i]));
        }

        mid++;
        int ans2 = 0;

        for(int i = 1; i <= n; i++){
            ans2 = max(ans2, abs(mid - a[i]));
        }

        cout << min(ans,ans2) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}