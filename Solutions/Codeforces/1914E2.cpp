/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 20:55:58
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Game with Marbles (Hard Version)
 *    source: https://codeforces.com/contest/1914/problem/E2
 *    submission: https://codeforces.com/contest/1914/submission/376538446
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log n)
 *    note: Just sort with the comparison between the best diff to take with both Alice and Bob
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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;

struct box{
    int a,b;

    box(int _a = 0, int _b = 0) : a(_a), b(_b) {};
};

bool cmp(const box& x, const box& y) {
    return x.a - 1 + x.b > y.a - 1 + y.b;
}

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
        vector<box> a(n+1);

        for(int i = 1; i <= n; i++){
            cin >> a[i].a;
        }
        for(int i = 1; i <= n; i++){
            cin >> a[i].b;
        }

        sort(all(a,1),cmp);

        ll suma = 0, sumb = 0;
        for(int i = 1; i <= n; i++){
            if(i&1) suma += a[i].a - 1;
            else sumb += a[i].b - 1;
        }

        cout << suma - sumb << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}