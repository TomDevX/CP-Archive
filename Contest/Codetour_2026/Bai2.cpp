/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-10-03 14:43:32
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    metacognition: 
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
    if(!fopen("Bai2.INP", "r")) return;
    freopen("Bai2.INP", "r", stdin);
    freopen("Bai2.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 5e5+5;

bool a[N];
int cur = 0;

struct Trie {
    int nxt[N][26];
    int cnt[N];
    int exist[N];
    int bin[N];
    int pool = 0;
    int tail = 0;
    
    int root;

    inline void reset_pool() noexcept {
        pool = tail = 0;
        exist[0] = cnt[0] = 0;
        for(int i = 0; i < 26; i++) nxt[0][i] = 0;
    }

    inline int alloc() noexcept {
        int id = (tail > 1) ? bin[--tail] : ++pool;
        exist[id] = cnt[id] = 0;
        for(int i = 0; i < 26; i++) nxt[id][i] = 0;
        return id;
    }

    inline void free_node(int id) noexcept {
        bin[tail++] = id;
    }

    void init() noexcept {
        root = alloc();
    }

    void add(const string& s) noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == 0) nxt[u][c] = alloc();
            u = nxt[u][c];
        }
        exist[u] = ++cur;
        a[cur] = 1;
    }

    void forbid(const string& s) noexcept {
        int u = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == 0) nxt[u][c] = alloc();
            u = nxt[u][c];
        }
        exist[u] = ++cur;
        a[cur] = 0;
    }

    void add_start(const string& s) noexcept {
        int u = root;
        cur++;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == 0) nxt[u][c] = alloc();
            u = nxt[u][c];
        }
        cnt[u] = cur;
        a[cur] = 1;
    }

    void forbid_start(const string& s) noexcept {
        int u = root;
        cur++;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == 0) nxt[u][c] = alloc();
            u = nxt[u][c];
        }
        cnt[u] = cur;
        a[cur] = 0;
    }

    int check(const string &s) const noexcept{
        int biggest = 0;
        int u = root;

        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[u][c] == 0) return biggest;
            u = nxt[u][c];
            biggest = max(biggest,cnt[u]);
        }
        
        biggest = max(biggest, exist[u]);

        return biggest;
    }
} norm,rev;

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int t;
    string s;

    cin >> t >> s;
 
    if(t == 1){
        norm.add(s);
        // reverse(all(s,0));
        // rev.add(s);
    }
    else if(t == 2){
        norm.forbid(s);
        // reverse(all(s,0));
        // rev.forbid(s);
    }
    else if(t == 3){
        norm.add_start(s);
    }
    else if(t == 4){
        norm.forbid_start(s);
    }
    else if(t == 5){
        reverse(all(s,0));
        rev.add_start(s);
    }
    else if(t == 6){
        reverse(all(s,0));
        rev.forbid_start(s);
    }
    else{
        int id = norm.check(s);
        reverse(all(s,0));
        id = max(id, rev.check(s));

        dbg(id,s); 

        cout << (a[id] ? 'Y' : 'N') << '\n';
    }
}

int main(){
    fastio;
    // setup();

    a[0] = 1;
    norm.init();
    rev.init();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}