/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-31 12:02:05
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Order statistic set
 *    source: https://oj.vnoi.info/problem/orderset
 *    submission: https://oj.vnoi.info/submission/12412425
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Trie
 *    complexity: O(n)
 *    note: Whole trie 
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
    if(!fopen("orderset.INP", "r")) return;
    freopen("orderset.INP", "r", stdin);
    freopen("orderset.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5*31+5;

struct Trie{
    int nxt[N][2];
    int cnt[N], exi[N];
    int bin[N];
    int pool = 1;
    int tail = 1;

    int alloc() noexcept {
        int id = (tail > 1) ? bin[--tail] : ++pool;
        cnt[id] = exi[id] = 0;
        nxt[id][0] = nxt[id][1] = 0;
        return id;
    }

    void free(int id) noexcept{
        bin[tail++] = id;
    }

    bool add(const string &s) noexcept{
        if(find(s)) return false;

        int u = 1;
        for(char ch : s){
            int c = ch - '0';
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;
        }
        exi[u]++;

        return true;
    }

    int find(const string &s) const noexcept{
        int u = 1;
        for(char ch : s){
            int c = ch - '0';
            if(!nxt[u][c]) return 0;
            u = nxt[u][c];
        }
        return u;
    }

    bool del(const string& s) noexcept{
        if(!find(s)) return false;

        int u = 1;
        for(int i = 0; i < sz(s); i++){
            int c = s[i] - '0';
            int v = nxt[u][c];
            if(--cnt[v] == 0){
                nxt[u][c] = 0;
                for(int j = i + 1; j < sz(s); j++){
                    int rem = nxt[v][s[j] - '0'];
                    nxt[v][s[j] - '0'] = 0;
                    free(v);
                    v = rem;
                }
                free(v);
            }
            u = v;
        }
        exi[u]--;

        return true;
    }

    int find_kth(int k) const noexcept{
        int res = 0;
        int u = 1;

        for(int i = 30; i >= 0; i--){
            for(int c = 0; c < 2; c++){
                if(!nxt[u][c]) continue;
                if(k <= cnt[nxt[u][c]]){
                    res += c*(1 << i);
                    u = nxt[u][c];
                    break;
                }
                k -= cnt[nxt[u][c]];
            }
        }

        return res;
    }

    int count(const string& s) const noexcept {
        int u = 1;
        int res = 0;

        for(char ch : s){
            int c = ch - '0';
            for(int i = 0; i < c; i++){
                if(!nxt[u][i]) continue;
                res += cnt[nxt[u][i]];
            }
            u = nxt[u][c];
        }

        return res;
    }
};

Trie trie;

// ----------------------- [ FUNCTIONS ] -----------------------
string toStr(int x){
    string res;
    for(int i = 30; i >= 0; i--){
        res += ((x >> i & 1) + '0');
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int q;
    cin >> q;

    int cnt = 0;
    while(q--){
        char type;
        int k;
        cin >> type >> k;

        if(type == 'I'){
            if(trie.add(toStr(k + 1e9))) cnt++;
        }
        else if(type == 'D'){
            if(trie.del(toStr(k + 1e9))) cnt--;
        }
        else if(type == 'K'){
            if(cnt >= k) cout << trie.find_kth(k) - 1e9 << '\n';
            else cout << "invalid\n";
        }
        else{
            cout << trie.count(toStr(k + 1e9)) << '\n';
        }
    }
    
    return NAH_I_WOULD_WIN;
}