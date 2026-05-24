/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-24 00:16:33
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: We Be Flipping (Hard Version)
 *    source: https://codeforces.com/contest/2229/problem/C2
 *    submission: https://codeforces.com/contest/2229/submission/375848874
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Adhoc, Math
 *    complexity: O(n)
 *    note: 
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
    if(!fopen("2229C2.INP", "r")) return;
    freopen("2229C2.INP", "r", stdin);
    freopen("2229C2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

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

        vi a(n+1);
        vll pref(n+1), suff(n+2);
        vector<bool> sign(n+1);

        ll ans = 0;
        int pos = 0;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
            ans += a[i];
            pref[i] = pref[i-1] + abs(a[i]);
            sign[i] = (a[i] > 0);
        }

        for(int i = n; i >= 1; i--){
            suff[i] = suff[i+1] + a[i];
        }

        for(int i = 1; i <= n; i++){
            if(a[i] > 0){
                ll sum = pref[i-1] - a[i] + suff[i+1];
                if(sum > ans){
                    ans = sum;
                    pos = i;
                }
            }
        }

        if(pos == 0){
            cout << "0\n\n";
            continue;
        }

        vi moves;
        int changed = 0;
        for(int i = pos-1; i >= 1; i--){
            if((sign[i] ^ changed)&1){
                moves.eb(i);
                changed = !changed;
            }
        }

        dbg(ans,tc);

        cout << sz(moves) + 1 << '\n';
        for(int i : moves) cout << i << ' ';
        cout << pos << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}