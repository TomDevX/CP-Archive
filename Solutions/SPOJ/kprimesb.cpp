/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-07-12 17:11:15
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Almost Prime Numbers Again
 *    source: https://www.spoj.com/problems/KPRIMESB/
 *    submission: https://www.spoj.com/status/ns=35853772
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math, Inclusion-Exclusion
 *    complexity: O(2^k)
 *    metacognition: Just do a normal inclusion-exclusion here but need to notice that prime numbers don't counts and edge case n = 0 - also need to handle the case lcm > n
 *    note: Typical inclusion-exclusion problem with 2^10 approach
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <bitset>

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
    if(!fopen("kprimesb.INP", "r")) return;
    freopen("kprimesb.INP", "r", stdin);
    freopen("kprimesb.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int K = 11, N = 1e6+2;

int primes[K];
int pref_primes[N];
bitset<N> sang;
int n,k;
int ans = 0;

// ----------------------- [ FUNCTIONS ] -----------------------
int gcd(int x, int y){
    while(y){
        int tmp = x%y;
        x = y;
        y = tmp;
    }
    return x;
}

int lcm(int x, int y){
    if(x/gcd(x,y) > (n + y - 1)/y) return n+1;
    return x/gcd(x,y) * y;
}

void sieve(){
    sang[0] = sang[1] = 1;
    for(int i = 2; i * i < N; i++){
        if(!sang[i]){
            for(int j = i * i; j < N; j += i) sang[j] = 1;
        }
    }

    for(int i = 2; i < N; i++){
        pref_primes[i] = pref_primes[i-1] + !sang[i];
    }
}

void rest(){
    ans = 0;
}

void backtrack(int idx, int cnt, int LCM){
    if(idx >= k){
        if(cnt == 0) return;

        if(cnt&1) ans += n/LCM;
        else ans -= n/LCM;

        return;
    }

    backtrack(idx+1,cnt,LCM);
    
    int nxt_LCM = lcm(LCM, primes[idx]);
    if(nxt_LCM > n) return;
    backtrack(idx+1,cnt+1,nxt_LCM);
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(int tc){
    cin >> n >> k;
    for(int i = 0; i < k; i++){
        cin >> primes[i];
        if(primes[i] >= n){
            i--;
            k--;
        }
    }

    backtrack(0,0,1);

    // for(int mask = 1; mask < (1 << k); mask++){
    //     int LCM = 1;
    //     for(int i = 0; i < k; i++){
    //         if(mask >> i & 1){
    //             LCM = lcm(LCM, primes[i]);
    //             if(LCM > n) break;
    //         }
    //     }

    //     int cnt = __builtin_popcount(mask);
    //     if(cnt&1){
    //         ans += n/LCM;
    //     }
    //     else ans -= n/LCM;
    // }

    if(n == 0){
        cout << "Case " << tc << ": " <<  0 << '\n';
    }
    else cout << "Case " << tc << ": " <<  n - (ans + 1 + pref_primes[n] - k) << '\n';
    
    rest();
}

int main(){
    fastio;
    setup();
    sieve();

    int tc = 1;
    cin >> tc;
    for(int t = 1; t <= tc; t++)
    {
        __TomDev(t);
    }
    return NAH_I_WOULD_WIN;
}