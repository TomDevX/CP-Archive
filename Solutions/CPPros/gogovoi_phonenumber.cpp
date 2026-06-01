/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-29 10:39:13
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phone Number
 *    source: https://oj.vnoi.info/problem/gogovoi_phonenumber
 *    submission: https://oj.vnoi.info/submission/12394655
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: Just simply check if some number ended during the iteration through current string
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
    if(!fopen("gogovoi_phonenumber.INP", "r")) return;
    freopen("gogovoi_phonenumber.INP", "r", stdin);
    freopen("gogovoi_phonenumber.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+5;

struct Trie{
    int child[N][10];
    int cnt[N];
    int exi[N];
    int pool = 1;

    void reset_pool() noexcept {
        pool = 0;
        alloc();
    }

    int alloc() noexcept {
        ++pool;
        cnt[pool] = exi[pool] = 0;
        for(int i = 0; i < 10; i++) child[pool][i] = 0;
        return pool;
    }

    bool add(const string& s) noexcept{
        int u = 1;
        
        for(char ch : s){
            int c = ch - '0';
            if(!child[u][c]) child[u][c] = alloc();
            u = child[u][c];
            if(exi[u]) return false;
            cnt[u]++;
        }
        if(cnt[u] > 1) return false;
        exi[u]++;

        return true;
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
    while(tc--){
        trie.reset_pool();

        int n;
        cin >> n;
        string s;

        bool ok = true;
        for(int i = 1; i <= n; i++){
            cin >> s;

            if(!ok) continue;
            if(!trie.add(s)){
                ok = false;
                continue;
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}