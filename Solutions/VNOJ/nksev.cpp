/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-25 15:38:10
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tách từ
 *    source: https://oj.vnoi.info/problem/nksev
 *    submission: https://oj.vnoi.info/submission/12393469
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n*100)
 *    note: First, this problem divide the string into parts, so we think of dp. If ok([i,j]) then dp[i] += dp[j] where dp[i] = ways to make string [1,i]. Now to check ok(substr), we can use hash with map, but it will be O(|S|*100*log2(n)) -> TLE. Notice that max size of each elements is only 100, so we can iterate on each i -> O(|S|*100). So how do we check? We make a trie of elements, and when iterating back we check how many are they (remember to reverse all elements string before adding them in)
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
    if(!fopen("nksev.INP", "r")) return;
    freopen("nksev.INP", "r", stdin);
    freopen("nksev.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 4e5+5, M = 3e5+5;
const ll MOD = 1337377;

struct Trie{
    int child[N][26];
    int exi[N];
    int pool = 0;

    int root = 1;

    Trie(){alloc();};

    int alloc() noexcept {
        return ++pool;
    }

    void add(const string& s) noexcept {
        int u = 1;
        for(char ch : s){
            char c = ch - 'a';
            if(!child[u][c]) child[u][c] = alloc();
            u = child[u][c];
        }
        exi[u]++;
    }
};

Trie trie;

ll dp[M];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;

    int n;
    cin >> n;
    string random_kid;
    for(int i = 1; i <= n; i++){
        cin >> random_kid;
        reverse(all(random_kid,0));
        trie.add(random_kid);
    }

    for(int i = 0; i < sz(s); i++){
        int u = 1;

        for(int j = i; j >= 0 && i - j < 100; j--){
            if(trie.child[u][s[j] - 'a']) u = trie.child[u][s[j] - 'a'];
            else break;
            
            dp[i] = (dp[i] + (j > 0 ? dp[j-1]*trie.exi[u] : 1LL*trie.exi[u]))%MOD;
        }
    }

    cout << dp[sz(s)-1];
    
    return NAH_I_WOULD_WIN;
}