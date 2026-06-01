/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 10:54:49
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Chuỗi ADN
 *    source: https://oj.vnoi.info/problem/gogovoi_adn
 *    submission: https://oj.vnoi.info/submission/12394803
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: Just traverse through the trie to count the best way
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
    if(!fopen("gogovoi_adn.INP", "r")) return;
    freopen("gogovoi_adn.INP", "r", stdin);
    freopen("gogovoi_adn.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2.5e6;

ll ans = 0;

struct Trie{
    int nxt[N][4];
    int cnt[N];
    int pool = 1;

    void reset_pool() noexcept {
        pool = 1;
        for(int i = 0; i < 4; i++) nxt[pool][i] = 0;
    }

    int getID(char c) const noexcept {
        if(c == 'A') return 0;
        if(c == 'C') return 1;
        if(c == 'G') return 2;
        return 3;
    }

    int alloc() noexcept{
        ++pool;
        cnt[pool] = 0;
        for(int i = 0; i < 4; i++) nxt[pool][i] = 0;
        return pool;
    }

    void add(const string& s) noexcept {
        int u = 1;

        for(char ch : s){
            int c = getID(ch);
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;
        }
    }

    void dfs(int u, int passed){
        ans = max(ans, 1LL*passed*cnt[u]);
        for(int c = 0; c < 4; c++){
            if(nxt[u][c]) dfs(nxt[u][c],passed+1);
        }
    }
};

Trie trie;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    for(int t  = 1; t <= tc; t++){
        trie.reset_pool();
        ans = 0;

        int n;
        cin >> n;

        string s;
        for(int i = 1; i <= n; i++){
            cin >> s;
            trie.add(s);
        }

        trie.dfs(1,0);
        cout << "Case " << t << ": " << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}