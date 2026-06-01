/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 11:17:21
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Type Printer
 *    source: https://oj.vnoi.info/problem/trie_tprinter
 *    submission: https://oj.vnoi.info/submission/12394968
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: Just like normal backtrack but on Trie. We prefer the one with less characters => less deletion.
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
    if(!fopen("trie_tprinter.INP", "r")) return;
    freopen("trie_tprinter.INP", "r", stdin);
    freopen("trie_tprinter.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e6+5;

vector<char> moves;

struct Trie{
    int nxt[N][26];
    int exi[N];
    int h[N];
    int pool = 1;

    int alloc() noexcept {
        return ++pool;
    }

    void add(const string& s) noexcept {
        int u = 1;
        for(char ch : s){
            int c = ch - 'a';
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
        }
        exi[u]++;
    }

    int make_h(int u) noexcept {
        for(int c = 0; c < 26; c++){
            if(nxt[u][c]) h[u] = max(h[u], make_h(nxt[u][c]) + 1);
        }
        return h[u];
    }

    void dfs(int u) const noexcept{
        for(int i = 1; i <= exi[u]; i++) moves.eb('P');
        vpii prior;
        for(int c = 0; c < 26; c++){
            if(nxt[u][c]){
                prior.eb(h[nxt[u][c]], c);
            }
        }
        sort(all(prior,0), [](const pii& a, const pii& b){return a.fi < b.fi;});

        for(const pii& p : prior){
            moves.eb(p.se + 'a');
            dfs(nxt[u][p.se]);
        }
        moves.eb('-');
    }
};

Trie trie;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int n;
    cin >> n;
    string s;

    for(int i = 1; i <= n; i++){
        cin >> s;
        trie.add(s);
    }

    trie.make_h(1);

    trie.dfs(1);

    while(moves.back() == '-') moves.pop_back();

    cout << sz(moves) << '\n';
    for(char move : moves) cout << move;
    
    return NAH_I_WOULD_WIN;
}