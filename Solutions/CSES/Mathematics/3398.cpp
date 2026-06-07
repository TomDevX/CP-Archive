/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-06-07 15:35:19
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: Permutation Rounds
 *    source: https://cses.fi/problemset/task/3398
 *    submission: https://cses.fi/problemset/result/17461968/
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Math
 *    complexity: O(n \log n)
 *    note: First, we need to find the needed steps of each element to go back to its original place first, and it will make a cycle, every elements in that cycle takes the same steps to go back to their base index. So we just need to get the lcm of all cycle -> all cycle can return to its original position. Since lcm can be very large and we need to get lcm by using a*b/gcd which costs us inversion to calculate gcd, we go back to the original meaning of lcm is that getting the max power of that factor. So we factorize the number using sieve with O(\log n) then get their max power
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <utility>
#include <numeric>
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
    #if !defined(LOCAL)
        freopen("/dev/null", "w", stderr);
    #endif
    if(!fopen("main.INP", "r")) return;
    freopen("main.INP", "r", stdin);
    freopen("main.OUT", "w", stdout);
}

// ----------------------- [ CONFIG & CONSTANTS ] -----------------------
const int N = 2e5+5;
const ll MOD = 1e9+7;

int sang[N];
int maxpow[N];
bitset<N> vis;

// ----------------------- [ FUNCTIONS ] -----------------------
void sieve(){
    iota(all(sang,2),2);
    for(int i = 2; i*i < N; i++){
        if(sang[i] != i) continue;
        for(int j = i*i; j < N; j+=i){
            sang[j] = i;
        }
    }
}

void phantich(int n){
    while(n > 1){
        int p = sang[n];
        int mu = 0;
        while(n%p == 0){
            mu++;
            n /= p;
        }

        maxpow[p] = max(maxpow[p], mu);
    }
}

ll binpow(int a, int k){
    ll res = 1;
    while(k){
        if(k&1) res = (res*a)%MOD;
        a = (a*a)%MOD;
        k >>= 1;
    }
    return res;
}

// ----------------------- [ MAIN ] -----------------------
void __TomDev(){
    sieve();

    int n;
    cin >> n;
    vi pos(n+1);
    for(int i = 1; i <= n; i++){
        cin >> pos[i];
    }

    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            int cur = i;
            int steps = 0;
            do{
                cur = pos[cur];
                vis[cur] = 1;
                steps++;
            }while(cur != i);
            phantich(steps);
        }
    }

    ll ans = 1;
    for(int i = 1; i <= n; i++){
        if(sang[i] == i){
            ans = (ans*binpow(i,maxpow[i]))%MOD;
        }
    }

    cout << ans;
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