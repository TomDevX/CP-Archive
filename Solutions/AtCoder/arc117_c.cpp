/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-01 22:31:37
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tricolor Pyramid
 *    source: https://atcoder.jp/contests/arc117/tasks/arc117_c
 *    submission: https://atcoder.jp/contests/arc117/submissions/77114069
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Pascal
 *    complexity: O(n)
 *    metacognition: Calculate all cells >< O(n*(n+1)/2) -> Related to pascal, turn each cell into math formula: current cell = -(ai + a{i+1})%3 with ai = value at the below floor at index i. Then use Pascal formula to calculate each element at bottom floor's contributions to the sum to the cell at top floor (target)
 *    note: Notice that this is Pascal triangle, so we can know each cell's contribution to the top cell. Just understand that each cell can either move left or right when going up, and suppose that we're at the top cell, we can either go left/right, but we need to go right exactly i-1 time to reach cell i at the bottom, so the left turns automatically are (N-1) - (i-1) (because go through N-1 floors). So we need to choose i floor to turn right which is (N-1)C(i) (but in the code I use 1-base-indexed so I do (N-1)C(i-1)). Total contribution of index i cell is (-1)^{N-1} * sum(1 -> n){(N-1)C(i-1) * a[i]} | we have -1 because our current cell = -(ai + a{i+1})%3 of the below floor (use to determine the problem statement requirement is that different color = other color and same color = still same color). And then just get and mod 3 and turn into 'B', 'W', 'R'
 Tips: infer the current cell = -(ai + a{i+1})%3 by we have colors 'B', 'W', 'R' equivalent to 0,1,2 and we have 0 + 1 + 2 = 0 (mod 3) => -(sum of 2 other color) = the other one | by the way if they are the same => p1 + p2 + x = 0 (mod 3) => x = -(p1 + p2) (mod 3). What a coincidence.
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("arc117_c.INP", "r")) return;
    freopen("arc117_c.INP", "r", stdin);
    freopen("arc117_c.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 4e5+5;

int a[N];

// ----------------------- [ FUNCTIONS ] -----------------------
int norm(int x){
    x %= 3;
    if(x < 0) x += 3;
    return x;
}

int Cnk(int n, int k){
    if(n < k) return 0;
    if(n == k || k == 0) return 1;
    return 2;
}

int lucas(int n, int k){
    int res = 1;
    while(n || k){
        res = (res * Cnk(n%3, k%3))%3;
        n /= 3;
        k /= 3;
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n;
    cin >> n;
    char c;
    for(int i = 1; i <= n; i++){
        cin >> c;
        if(c == 'B') a[i] = 0;
        else if(c == 'W') a[i] = 1;
        else a[i] = 2;
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans = (ans + lucas(n-1,i-1)*a[i])%3;
    }

    if((n-1)&1) ans = norm(-ans);

    switch(ans){
        case 0:
            cout << 'B';
            break;
        case 1:
            cout << 'W';
            break;
        default:
            cout << 'R';
    }
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