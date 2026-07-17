/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-23 20:22:25
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Chuỗi từ
 *    source: https://oj.vnoi.info/problem/chain2
 *    submission: https://oj.vnoi.info/submission/12364982
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: Just dfs down the trie tree and check
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
    if(!fopen("chain2.INP", "r")) return;
    freopen("chain2.INP", "r", stdin);
    freopen("chain2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e5;

int ans = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
struct Trie{
    int child[N][26];
    int exist[N];
    int pool = 0;

    Trie(){
        alloc();
    };

    int alloc() noexcept{
        return ++pool;
    }

    void add(const string& s) noexcept{
        int u = 1;

        for(char ch : s){
            int c = ch - 'a';
            if(!child[u][c]){
                child[u][c] = alloc();
            }
            u = child[u][c];
        }
        exist[u] = 1;
    }

    void dfs(int u, int cnt){
        bool ended = true;
        for(int c = 0; c < 26; c++){
            int v = child[u][c];
            if(v){
                dfs(v, cnt + (exist[v] > 0));
                ended = false;
            }
        }
        if(ended) ans = max(ans,cnt);
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

    trie.dfs(1,0);

    cout << ans << '\n';
    
    return NAH_I_WOULD_WIN;
}