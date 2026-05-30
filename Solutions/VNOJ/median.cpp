/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-30 10:57:04
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Phần tử trung vị
 *    source: https://oj.vnoi.info/problem/median
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
    if(!fopen("median.INP", "r")) return;
    freopen("median.INP", "r", stdin);
    freopen("median.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int MOD = 65535, N = 3e4+5;
int seed,mul,add,n,k;

// ----------------------- [ FUNCTIONS ] -----------------------
int jump(int x){
    return (x*mul + add)%MOD;
}

struct Trie{
    int nxt[N][10];
    int cnt[N], exi[N];
    int bin[N];
    int pool = 1;
    int tail = 1;

    void reset() noexcept {
        tail = pool = 1;
        for(int i = 0; i < 10; i++) nxt[pool][i] = 0;
    }

    int alloc() noexcept {
        int id = (tail > 1) ? bin[--tail] : ++pool;
        cnt[id] = exi[id] = 0;
        for(int i = 0; i < 10; i++) nxt[id][i] = 0;
        return id; 
    }

    void free(int id) noexcept{
        bin[tail++] = id;
    }

    void add(int x) noexcept{
        int u = 1;
        int div = 1e4;
        while(div){
            int c = x/div;
            if(!nxt[u][c]) nxt[u][c] = alloc();
            u = nxt[u][c];
            cnt[u]++;

            x %= div;
            div /= 10;
        }
        exi[u]++;
    }

    const string toStr(int x) const noexcept {
        string s;
        for(int i = 0; i < 5; i++){
            s += (x%10) + '0';
            x /= 10;
        }
        reverse(all(s,0));
        return s;
    }

    void del(int x){
        string s = toStr(x);

        int u = 1;
        for(int i = 0; i < 5; i++){
            int c = s[i] - '0';

            cnt[nxt[u][c]]--;

            if(!cnt[nxt[u][c]]){
                for(int j = i; j < 5; j++){
                    int rem = nxt[u][s[j] - '0'];
                    nxt[u][s[j] - '0'] = 0;
                    if(u > 1) free(u);
                    u = rem;
                }
                free(u);

                return;
            }

            u = nxt[u][c];
        }
        exi[u]--;
    }

    int find_dict(int pos){
        int res = 0;

        for(int u = 1; pos > exi[u];){
            pos -= exi[u];
            for(int c = 0; c < 10; c++){
                if(!nxt[u][c]) continue;
                if(pos <= cnt[nxt[u][c]]){
                    res = res*10 + c;
                    u = nxt[u][c];
                    break;
                }
                pos -= cnt[nxt[u][c]];
            }
        }

        return res;
    }
};

Trie trie;

// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    int tc;
    cin >> tc;
    for(int t = 1; t <= tc; t++){
        cin >> seed >> mul >> add >> n >> k;

        ll l = seed, r = seed;
        trie.add(l);
        for(int i = 1; i < k; i++){
            r = jump(r);
            trie.add(r);
        }

        ll ans = trie.find_dict((k + 1)>>1);

        for(int i = k; i < n; i++){
            trie.del(l);
            l = jump(l);
            
            r = jump(r);
            trie.add(r);

            ans = (ans + trie.find_dict((k + 1)>>1))%MOD;
        }

        cout << "Case #" << t << ": " << ans << '\n';

        trie.reset();
    }
    
    return NAH_I_WOULD_WIN;
}