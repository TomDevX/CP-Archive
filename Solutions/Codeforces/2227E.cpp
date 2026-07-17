/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-01 14:37:52
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: It All Went Sideways
 *    source: https://codeforces.com/contest/2227/problem/E
 *    submission: https://codeforces.com/contest/2227/submission/373236254
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n)
 *    note: Let S = total cubes, K = sum(i: 1 -> n){suffix_min[i]} - also means the number of cubes which stay stable after changing the gravity, because just observe that the min layer will block the left blocks with the same layer from moving. When we haven't remove any cube, our answer is S - K. Now to maximize this answer, we need to -1 in the block that affects to the most suffix_min.
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
    if(!fopen("2227E.INP", "r")) return;
    freopen("2227E.INP", "r", stdin);
    freopen("2227E.OUT", "w", stdout);
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
        vi a(n+1);
        ll S = 0;
        for(int i = 1; i <= n; i++) cin >> a[i], S += a[i];

        vi suff(n+2, 1e9);
        ll K = 0;
        for(int i = n;i >= 1; i--){
            suff[i] = min(suff[i+1], a[i]);
            K += suff[i];
        }

        vi L(n+1,-1);
        int r = n;
        for(int l = n-1; l >= 0; l--){ // find next suffix min after r
            if(a[l] < a[r]){
                L[r] = l;
                r = l;
            }
        }

        ll changed = 0;
        for(int i = 1; i <= n; i++){
            if(L[i] == -1) continue;
            changed = max(changed, 1LL* i - L[i]); // number of elements that this suffix_min affect
        }

        // ori answer: S - K
        cout << S - 1 - K  + changed << '\n'; // S become S-1 (removing 1 cube), add changed var to add the optimized answer
        // if you are wondering what about the case that we don't remove any cube -> that's always a loss
    }
    
    return NAH_I_WOULD_WIN;
}