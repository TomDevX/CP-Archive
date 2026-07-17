/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-20 16:02:37
 *    country: Vietnam - VNM
 *    My Repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Minimal Rotation
 *    source: https://cses.fi/problemset/task/1110
 *    submission: https://cses.fi/problemset/result/17233962/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Hash
 *    complexity: O(n \log n)
 *    note: Just double the string and check all substring length n if they are smaller than the best one. In order to check faster, we use hash.
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
#define all(x,bonus) (x).begin()+(bonus),(x).end()
#define sub(x, st, ed) (std::begin((x)) + (st)), (std::begin((x)) + (ed) + 1)
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
    if(!fopen("1110.INP", "r")) return;
    freopen("1110.INP", "r", stdin);
    freopen("1110.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e6+5;
const ll MOD1 = 1234567891;
const ll MOD2 = 1e9+4567;
ll base = 31;

struct HashKey{
    ll h1,h2;
    const bool operator==(const HashKey& o) const{
        return h1 == o.h1 && h2 == o.h2;
    }
};

HashKey POW[N];
HashKey Hash[2*N];
int pool = 0;

void init_pow(){
    POW[0] = {1,1};
    for(int i = 1; i < N; i++){
        POW[i].h1 = (POW[i-1].h1*base)%MOD1;
        POW[i].h2 = (POW[i-1].h2*base)%MOD2;
    }
}

struct Precompute {
    Precompute() {
        init_pow(); 
    }
} __init;

struct PolyHash{
    HashKey* h = nullptr;
    int len = 0;
    const string& s;

    PolyHash(const string& _s) : s(_s) {
        len = sz(s) - 1;
        h = &Hash[pool];
        pool += len+1;

        for(int i = 1; i <= len; i++){
            h[i].h1 = (h[i-1].h1*base + s[i] - 'a' + 1)%MOD1;
            h[i].h2 = (h[i-1].h2*base + s[i] - 'a' + 1)%MOD2;
        }
    }

    HashKey get(int l, int r){
        int seg = r-l+1;
        int res1 = (h[r].h1 - h[l-1].h1*POW[r-l+1].h1)%MOD1;
        int res2 = (h[r].h2 - h[l-1].h2*POW[r-l+1].h2)%MOD2;
        if(res1 < 0) res1 += MOD1;
        if(res2 < 0) res2 += MOD2;
        return {res1,res2};
    }

    const bool isGreater(int l, int r, int u, int v){
        if(get(l,r) == get(u,v)) return false;

        int L = 0, R = r-l, LCP = -1;
        while(L <= R){
            int mid = L + ((R-L)>>1);

            if(get(l, l + mid) == get(u, u + mid)){
                LCP = mid;
                L = mid+1;
            }
            else R = mid-1;
        }

        return s[l + LCP + 1] > s[u + LCP + 1];
    }
};

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
int main(){
    fastio;
    setup();
    
    string s;
    cin >> s;
    int n = sz(s);
    s = '#' + s + s;

    PolyHash h(s);

    int best = 1;
    for(int i = 2; i + n - 1 < sz(s); i++){
        if(h.isGreater(best, best + n - 1, i, i + n - 1)){
            best = i;
        }
    }

    cout << s.substr(best,n);
    
    return NAH_I_WOULD_WIN;
}