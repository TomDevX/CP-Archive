/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 18:13:16
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: ADAINDEX - Ada and Indexing
 *    source: https://www.spoj.com/problems/ADAINDEX/
 *    submission: https://www.spoj.com/status/ns=35771587#
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: Typical Trie
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <cstring>

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
    if(!fopen("adaindex.INP", "r")) return;
    freopen("adaindex.INP", "r", stdin);
    freopen("adaindex.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;

struct Trie{
    int child[N][26];
    int cnt[N];
    int exist[N];
    int pool = -1;

    Trie(){
        alloc();
    };

    int alloc() noexcept{
        int id = ++pool;
        exist[id] = cnt[id] = 0;
        memset(child[id], -1, 26 * sizeof(int));
        return id;
    }

    void add(const string &s) noexcept {
        int u = 0;
        for(char ch : s){
            int c = ch-'a';
            if(child[u][c] == -1){
                child[u][c] = alloc();
            }
            u = child[u][c];
            cnt[u]++;
        }
        exist[u]++;
    }

    int find(const string& s) const noexcept {
        int u = 0;
        for(char ch : s){
            int c = ch - 'a';
            if(child[u][c] == -1) return 0;
            u = child[u][c];
        }
        return u;
    }

    int count(const string &s) const noexcept {
        int u = find(s);
        return cnt[u];
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

    string s;
    for(int i = 1; i <= n; i++){
        cin >> s;
        trie.add(s);
    }

    while(q--){
        string s;
        cin >> s;
        cout << trie.count(s) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}