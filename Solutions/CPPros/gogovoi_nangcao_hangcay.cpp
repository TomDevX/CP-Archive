/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-27 18:15:34
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Bài 4: Hàng cây
 *    source: https://oj.vnoi.info/problem/gogovoi_nangcao_hangcay
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
    if(!fopen("gogovoi_nangcao_hangcay.INP", "r")) return;
    freopen("gogovoi_nangcao_hangcay.INP", "r", stdin);
    freopen("gogovoi_nangcao_hangcay.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e4+2, K = 8;
const ll MOD = 1e9+7;


struct box{
    int type, h;
    
    box(int _type = 0, int _h = 0) : type(_type), h(_h) {};
};

box a[N];

struct modll{
    ll val = 0;
    
    modll() : val(0) {};
    modll(ll x) : val(norm(x)) {};
    
    ll norm(ll x) const noexcept {
        x %= MOD;
        if(x < 0) x += MOD;
        return x;
    }
    
    modll binpow(ll k) const noexcept {
        modll res = 1;
        modll x = *this;
        while(k){
            if(k & 1) res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }
    
    // set operators
    void operator +=(modll x) noexcept { val = (val+x.val)%MOD; }
    void operator -=(modll x) noexcept { val = norm(val-x.val); }
    void operator *=(modll x) noexcept { val = (1ULL*val*x.val)%MOD; }
    void operator /=(modll x) noexcept { *this *= x.binpow(MOD-2); }
    
    // operators
    modll operator +(modll x) const noexcept { return  (val + x.val)%MOD; }
    modll operator -(modll x) const noexcept { return norm(val - x.val); }
    modll operator *(modll x) const noexcept { return (1ULL*val * x.val)%MOD; }
    modll operator /(modll x) const noexcept { return *this * x.binpow(MOD-2); }
    
    // input/output
    friend std::ostream& operator <<(std::ostream& os, modll &x) noexcept { return os << x.val; }
    friend std::istream& operator >>(std::istream& is, modll &x) noexcept {
        ll inp_val;
        is >> inp_val;
        x = modll(inp_val);
        return is;
    }
};

modll dp[N][1 << K];

// ----------------------- [ FUNCTIONS ] -----------------------


// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,k;
    cin >> n >> k;

    for(int i = 1; i <= n; i++){
        cin >> a[i].type >> a[i].h;
    }

    dp[0][0] = 1;

    for(int i = 0; i < n; i++){
        for(int mask = 0; mask < (1 << k); mask++){
            
        }
    }
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