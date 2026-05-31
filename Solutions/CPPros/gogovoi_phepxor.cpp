/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-31 22:42:04
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phép XOR
 *    source: https://oj.vnoi.info/problem/gogovoi_phepxor
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
using vb = vector<bool>;
using vs = vector<string>;
using vpii = vector<pair<int,int>>;
using vpill = vector<pair<int,long long>>;
using vpll = vector<pair<long long,long long>>;

void setup(){
    if(!fopen("gogovoi_phepxor.INP", "r")) return;
    freopen("gogovoi_phepxor.INP", "r", stdin);
    freopen("gogovoi_phepxor.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 3e6+5, LOG = 29;

struct Trie{
    int nxt[N][2];
    int cnt[N], exi[N];
    int bin[N];
    int pool = 1, tail = 1;

    void reset() noexcept{
        pool = tail = 1;
        nxt[1][0] = nxt[1][1] = 0;
    }

    int alloc() noexcept{
        int id = (tail > 1) ? bin[--tail] : ++pool;
        cnt[id] = exi[id] = 0;
        nxt[id][0] = nxt[id][1] = 0;
        return id;
    }

    void add(const string& s) noexcept{
        int u = 1;
        for(char ch : s){
            int c = ch - '0';
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;
        }
        exi[u]++;
    }

    int get_max_xor(const string& s) const noexcept{
        int u = 1;
        int res = 0;

        int pow = LOG;
        for(int i = 0; i <= LOG; i++, pow--){
            int c = s[i] - '0';
            if(c){
                if(nxt[u][0]){
                    u = nxt[u][0];
                    res += (1 << pow);
                }
                else{
                    u = nxt[u][1];
                }
            }
            else{
                if(nxt[u][1]){
                    u = nxt[u][1];
                    res += (1 << pow);
                }
                else{
                    u = nxt[u][0];
                }
            }
        }

        return res;
    }
};

Trie trie;

// ----------------------- [ FUNCTIONS ] -----------------------
string toStr(int x){
    string res;
    for(int i = LOG; i >= 0; i--){
        res += ((x >> i) & 1) + '0';
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    while(tc--){
        trie.reset();

        int n;
        cin >> n;
        vi a(n+1);
        for(int i = 1; i <= n; i++) cin >> a[i];

        trie.add(toStr(a[1]));

        int ans = 0;
        for(int i = 2; i <= n; i++){
            ans = max(ans, trie.get_max_xor(toStr(a[i])));
            if(i < n) trie.add(toStr(a[i]));
        }

        cout << ans << '\n';
    }
    
    return NAH_I_WOULD_WIN;
}