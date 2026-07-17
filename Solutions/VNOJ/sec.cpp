/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 09:45:21
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tin mật
 *    source: https://oj.vnoi.info/problem/sec
 *    submission: https://oj.vnoi.info/submission/12394516
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: If the string in the first set ended, it may be our queried string -> +1. If our queried string ended, which string takes queried string as prefix will get +1
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
    if(!fopen("sec.INP", "r")) return;
    freopen("sec.INP", "r", stdin);
    freopen("sec.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

struct Trie{
    int child[N][2];
    int cnt[N];
    int exi[N];
    int pool = 0;

    Trie(){
        alloc();
    }

    int alloc() noexcept {
        return ++pool;
    }
};

Trie trie;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n,q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++){
        int m;
        cin >> m;
        int c;
        
        // trie.add()
        int u = 1;
        for(int j = 1; j <= m; j++){
            cin >> c;
            if(!trie.child[u][c]) trie.child[u][c] = trie.alloc();
            u = trie.child[u][c];
            trie.cnt[u]++;
        }
        trie.exi[u]++;
    }

    while(q--){
        int m;
        cin >> m;

        int ans = 0;
        int c;
        bool good = true;
        
        // trie.count();
        int u = 1;
        for(int i = 1; i <= m; i++){
            cin >> c;

            if(!good) continue;
            if(!trie.child[u][c]){
                good = false;
                continue;
            }

            u = trie.child[u][c];
            if(trie.exi[u]) ans += trie.exi[u];
        }
        ans += (good ? trie.cnt[u] - trie.exi[u] : 0);

        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}