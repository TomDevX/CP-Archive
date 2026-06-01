/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-01 16:21:46
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Tổng XOR lớn nhất
 *    source: https://oj.vnoi.info/problem/gogovoi_sumxor
 *    submission: https://oj.vnoi.info/submission/12415495
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n \log maxn)
 *    note: Trie on bit
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
    if(!fopen("gogovoi_sumxor.INP", "r")) return;
    freopen("gogovoi_sumxor.INP", "r", stdin);
    freopen("gogovoi_sumxor.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e6+5;

struct Trie{
    int nxt[N][2];
    int cnt[N], exi[N];
    int pool = 1;

    int alloc() noexcept{
        return ++pool;
    }

    void add(int x) noexcept{
        int u = 1;
        for(int i = 29; i >= 0; i--){
            int c = (x >> i & 1);
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;
        }
        exi[u]++;
    }

    int get_best_xor(int x) const noexcept{
        int u = 1;
        int res = 0;
        for(int i = 29; i >= 0; i--){
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
    
    int n;
    cin >> n;
    vi a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vi pref(n+1);

    trie.add(0);
    int ans = 0;

    for(int i = 1; i <= n; i++){
        pref[i] = pref[i-1]^a[i];
        ans = max(ans, trie.get_best_xor(pref[i]));
        trie.add(pref[i]);
    }

    cout << ans;
    
    return NAH_I_WOULD_WIN;
}