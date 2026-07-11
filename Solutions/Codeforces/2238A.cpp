/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-09 21:33:16
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Another Puzzle from Papyrus
 *    source: https://codeforces.com/contest/2238/problem/A
 *    submission: https://codeforces.com/contest/2238/submission/381867579
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Greedy
 *    complexity: O(n\logn)
 *    metacognition: First just count normally if we don't reorder. The second count is reorder, best way to reorder is to sort the array to match min - min, mid - mid, max - max. If there's a < b, we'll never reach it => -1
 *    note: Count normally and then sort the array and count again to get the maximum ans
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
    if(!fopen("2238A.INP", "r")) return;
    freopen("2238A.INP", "r", stdin);
    freopen("2238A.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int INF = 2e9;
const int N = 102;

int a[N], b[N];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,c;
    cin >> n >> c;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    int ans1 = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] < b[i]){
            ans1 = INF;
            break;
        }
        ans1 += a[i] - b[i];
    }

    sort(sub(a,1,n));
    sort(sub(b,1,n));

    int ans2 = c;
    for(int i = 1; i <= n; i++){
        if(a[i] < b[i]){
            ans2 = INF;
            break;
        }
        ans2 += a[i] - b[i];
    }

    cout << (min(ans1,ans2) == INF ? -1 : min(ans1,ans2)) << '\n';
}   

int main(){
    fastio;
    setup();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}