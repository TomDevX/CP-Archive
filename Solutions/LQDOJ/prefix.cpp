/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 20:53:21
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Trie - PREFIX
 *    source: https://lqdoj.edu.vn/problem/prefix
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
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
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("prefix.INP", "r")) return;
    freopen("prefix.INP", "r", stdin);
    freopen("prefix.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e6+5;

ll ans = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
struct Trie{
    int child[N][26];
    int exi[N], cnt[N];
    int pool = 0;

    Trie(){
        alloc();
    }

    int alloc() noexcept {
        return ++pool;
    }

    void add(const string& s) noexcept {
        int u = 1;

        for(char ch : s){
            int c = ch - 'a';
            if(!child[u][c]) child[u][c] = alloc();
            u = child[u][c];
            cnt[u]++;
        }
        exi[u]++;
    }

    void dfs(int u) noexcept{
        ans += exi[u]*(cnt[u] - exi[u]);
        ans += exi[u]*((exi[u]-1)>>1LL);
        for(int c = 0; c < 26; c++){
            int v = child[u][c];
            if(v){
                dfs(v);
            }
        }
    }
};

Trie trie;

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

    trie.dfs(1);

    cout << ans+1 << '\n';
    
    return NAH_I_WOULD_WIN;
}