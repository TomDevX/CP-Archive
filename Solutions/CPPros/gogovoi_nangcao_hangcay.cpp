/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-27 18:15:34
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bài 4: Hàng cây
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_hangcay
 *    submission: https://oj.vnoi.info/submission/12854733
 *    status: AC
 * ----------------------------------------------------------
 *    tags: DP Bitmask, BIT
 *    complexity: O(2^k \cdot n \cdot \log_2 H)
 *    metacognition: Maybe we need a dp[N][H][MASK] = processed to pos N, last one has height of H, and MASK of types are kept >< that's too many arguments so we need to see which is useless and remove it. We can we can see that for each H at ith index, we can easily query the past states before ith index with BIT (query on the mask and index from 1 -> i - 1) -> dp turns into dp[H][mask] and query using BIT
 *    note: dp[H][mask] = ways for current last height is H and chosen types is mask. Run through each i index, and query 1 -> i-1 states using BIT
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
    if(!fopen("gogovoi_nangcao_hangcay.INP", "r")) return;
    freopen("gogovoi_nangcao_hangcay.INP", "r", stdin);
    freopen("gogovoi_nangcao_hangcay.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e4+2, H = 1e4+2, K = 8;
const ll MOD = 1e9+7;

int n,k;

struct box{
    int type, h;
    
    box(int _type = 0, int _h = 0) : type(_type), h(_h) {};
};

struct modll{
    ll val = 0;
    
    modll() : val(0) {};
    modll(ll x) : val(norm(x)) {};
    
    ll norm(ll x) const noexcept {
        x %= MOD;
        if(x < 0) x += MOD;
        return x;
    }
    
    modll binpow(ll exp) const noexcept {
        modll res = 1;
        modll x = *this;
        while(exp){
            if(exp & 1) res *= x;
            x *= x;
            exp >>= 1;
        }
        return res;
    }
    
    // set operators
    void operator +=(modll x) noexcept {
        val += x.val;
        if(val >= MOD) val -= MOD;
    }
    void operator -=(modll x) noexcept { 
        val -= x.val;
        if(val < 0) val += MOD;
    }
    void operator *=(modll x) noexcept { val = (1ULL*val*x.val)%MOD; }
    void operator /=(modll x) noexcept { *this *= x.binpow(MOD-2); }
    
    // operators
    modll operator +(modll x) const noexcept { 
        ll res = val + x.val;
        return modll(res >= MOD ? res - MOD : res);
    }
    modll operator -(modll x) const noexcept { 
        ll res = val - x.val;
        return modll(res < 0 ? res + MOD : res);
    }
    modll operator *(modll x) const noexcept { return (1ULL*val * x.val)%MOD; }
    modll operator /(modll x) const noexcept { return *this * x.binpow(MOD-2); }
    
    // input/output
    friend std::ostream& operator <<(std::ostream& os, modll x) noexcept { return os << x.val; }
    friend std::istream& operator >>(std::istream& is, modll &x) noexcept {
        ll inp_val;
        is >> inp_val;
        x = modll(inp_val);
        return is;
    }
};

struct BIT{
    modll bit[N][1 << K];

    modll get(int mask, int pos){
        modll res = 0;
        for(; pos; pos -= pos&-pos) res += bit[pos][mask];
        return res;
    }

    modll query(int mask, int l, int r){
        return get(mask,r) - (l-1 == 0 ? 0 : get(mask,l-1));
    }

    void update(int mask, int pos, modll val){
        for(; pos < H; pos += pos&-pos){
            bit[pos][mask] += val;
        }
    }
}bit;

box a[N];
modll dp[H][1 << K];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    cin >> n >> k;

    for(int i = 1; i <= n; i++){
        cin >> a[i].type >> a[i].h;
        a[i].type--;
    }

    dp[0][0] = 1;
    // bit.update(0,0,1); (this can help replacing mask == (1 << a[i].type) but BIT can't process 0 index)

    for(int i = 1; i <= n; i++){
        for(int mask = 0; mask < (1 << k); mask++){
            if(!(mask >> a[i].type & 1)) continue;

            modll old_val = dp[a[i].h][mask];
            dp[a[i].h][mask] += bit.query(mask, 1, a[i].h-1) + bit.query(mask ^ (1 << a[i].type), 1, a[i].h-1);
            
            if(mask == (1 << a[i].type)){
                dp[a[i].h][mask] += 1;
            }

            bit.update(mask, a[i].h, dp[a[i].h][mask] - old_val);
        }
    }

    cout << bit.query((1 << k) - 1, 1, H-1);
}

int main(){
    fastio;
    setup();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}
