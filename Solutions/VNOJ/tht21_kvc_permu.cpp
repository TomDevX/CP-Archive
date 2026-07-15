/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-15 15:27:28
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Hoán vị không bất động
 *    source: https://oj.vnoi.info/problem/tht21_kvc_permu
 *    submission: https://oj.vnoi.info/submission/12735516
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Inclusion-Exclusion, Math
 *    complexity: O(m + T)
 *    metacognition: We just need to calculate the permutation as n! as normal, then remove out the violated cases. So we need to remove the cases which have at least 1 violation, but after removing it, we accidentally add too much for the 2 violations, 3 violations cases => apply inclusion-exclusion combine with Combinatorics to avoid bitmask 
 *    note: We remove violated permutations from n! permutations. To count the violated permutations, we use inclusion-exclusion to count only 1 case of each violation numbers
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
    if(!fopen("tht21_kvc_permu.INP", "r")) return;
    freopen("tht21_kvc_permu.INP", "r", stdin);
    freopen("tht21_kvc_permu.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 1e5+2;
const ll MOD = 1e9+7;

int avail[N];
ll fac[N], inv[N];

// ----------------------- [ FUNCTIONS ] -----------------------
ll binpow(ull x, ll k){
    ull res = 1;
    while(k){
        if(k&1) res = (res*x)%MOD;
        x = (x*x)%MOD;
        k >>= 1;
    }
    return res;
}

void precalc(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = (fac[i-1]*i)%MOD;

    inv[N-1] = binpow(fac[N-1],MOD-2);

    for(int i = N-2; i >= 0; i--){
        inv[i] = (inv[i+1]*(i+1))%MOD;
    }
}

ll norm(ll x){
    x %= MOD;
    if(x < 0) x += MOD;
    return x;
}

ll nck(int n, int k){
    if(k > n) return 0;
    return (fac[n]*inv[n-k])%MOD*inv[k]%MOD;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    int m,T;
    cin >> m >> T;
    for(int i = 1; i <= T; i++){
        int l,r;
        cin >> l >> r;
        avail[l]++;
        avail[r+1]--;
    }

    int affected = 0;

    for(int i = 1; i <= m; i++){
        avail[i] += avail[i-1];
        if(avail[i] > 0) affected++;
    }

    ll ans = fac[m];

    // dbg(inv[1],inv[N-1]);
    for(int i = 1; i <= affected; i++){
        if(i&1){
            ans = norm(ans - norm(nck(affected,i)*fac[m-i]));
        }
        else{
            ans = norm(ans + norm(nck(affected,i)*fac[m-i]));
        }
    }

    cout << ans;
}

int main(){
    fastio;
    setup();
    precalc();

    int tc = 1;
    //cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev();
    }
    return NAH_I_WOULD_WIN;
}