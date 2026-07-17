/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-01 16:43:36
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Đa tập
 *    source: https://oj.vnoi.info/problem/gogovoi_multiset
 *    submission: https://oj.vnoi.info/submission/12415693
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n \log \text{max}(n))
 *    note: Typical trie
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
    if(!fopen("gogovoi_multiset.INP", "r")) return;
    freopen("gogovoi_multiset.INP", "r", stdin);
    freopen("gogovoi_multiset.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int LG = 29, N = 6e6+5;

struct Trie{
    int nxt[N][2];
    int cnt[N];
    int bin[N];
    int pool = 1, tail = 1;

    int alloc() noexcept{
        int id = (tail > 1) ? bin[--tail] : ++pool;
        cnt[id] = 0;
        nxt[id][0] = nxt[id][1] = 0;
        return id;
    }

    void free(int u) noexcept{
        bin[tail++] = u;
    }

    void add(int x) noexcept{
        int u = 1;
        for(int i = LG; i >= 0; i--){
            int c = (x >> i) & 1;
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;
        }
    }

    void del(int x) noexcept{
        int u = 1;
        for(int i = LG; i >= 0; i--){
            int c = (x >> i & 1);
            
            int v = nxt[u][c];

            if(--cnt[v] == 0){
                nxt[u][c] = 0;
                for(int j = i - 1; j >= 0; j--){
                    c = (x >> j & 1);
                    int rem = nxt[v][c];
                    nxt[v][c] = 0;
                    free(v);
                    v = rem;
                }
                free(v);
                return;
            }

            u = v;
        }
    }

    int get_max_xor(int x) const noexcept{
        int u = 1;
        int res = 0;

        for(int i = LG; i >= 0; i--){
            int c = (x >> i & 1);
            if(nxt[u][c^1]){
                u = nxt[u][c^1];
                res += (1 << i);
            }
            else u = nxt[u][c];
        }

        return res;
    }
};

Trie trie;
// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int q;
    cin >> q;

    trie.add(0);

    char type;
    int x;
    while(q--){
        cin >> type >> x;

        if(type == '+'){
            trie.add(x);
        }
        else if(type == '-'){
            trie.del(x);
        }
        else cout << trie.get_max_xor(x) << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}