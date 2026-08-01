/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-08-01 16:47:53
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
#include <cstring>

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
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1 << 10;
const ll MOD = 1e9+7;


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

modll dp[2][N];

// ----------------------- [ FUNCTIONS ] -----------------------
void rest(int id){
    memset(dp[id], 0, sizeof(dp[id]));
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int n,m;
    cin >> n >> m;

    dp[0][0] = 1;
    
    for(int j = 0; j < m; j++){
        for(int i = 0; i < n; i++){
            rest(1);
            for(int mask = 0; mask < (1 << n); mask++){

                // occupied
                if(mask >> i & 1){
                    dp[1][mask ^ (1 << i)] += dp[0][mask];
                }

                // not occupied
                else{
                    // vertical
                    if(i + 1 < n && !(mask >> (i+1) & 1)){
                        dp[1][mask | (1 << (i+1))] += dp[0][mask];
                    }

                    // horizontal
                    dp[1][mask | (1 << i)] += dp[0][mask];
                }
            }
            swap(dp[0], dp[1]);
        }
    }

    cout << dp[0][0];
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