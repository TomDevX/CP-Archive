/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-02 08:51:47
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: S-Nim
 *    source: https://open.kattis.com/problems/snim
 *    submission: https://open.kattis.com/submissions/19875434
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Game theory, Grundy
 *    complexity: O(n*k)
 *    metacognition: Grundy
 *    note: Use Grundy with precalc G(x)
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("snim.INP", "r")) return;
    freopen("snim.INP", "r", stdin);
    freopen("snim.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int K = 102, N = 1e4+1;

int moves[K];
int G[N];
int k;
int vis[N];

// ----------------------- [ FUNCTIONS ] -----------------------
void precalc(){
    for(int i = 1; i <= 10000; i++){
        for(int j = 1; j <= k; j++){
            if(i >= moves[j]) vis[G[i - moves[j]]] = i;
        }
        int mex = 0;
        while(vis[mex] == i) mex++;
        G[i] = mex;
    }
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> k;
    for(int i = 1; i <= k; i++) cin >> moves[i];
    precalc();


    int q;
    cin >> q;
    int n;
    while(q--){
        cin >> n;
        int x;
        int ans = 0;
        for(int i = 1; i <= n; i++){
            cin >> x;
            ans ^= G[x];
        }
        cout << (ans == 0 ? 'L' : 'W');
    }

}

int main(){
    fastio;
    setup();

    int tc = 1;
    // cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}